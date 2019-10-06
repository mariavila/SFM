#include "Reconstruction.h"

using namespace std;
using namespace cv;

Reconstruction::Reconstruction(){
}

Reconstruction::Reconstruction(string name, string out_filename_path){
  this->name = name;
  this->parser = Parser(out_filename_path);
}

string Reconstruction::get_name(){
  return this->name;
}


void Reconstruction::reconstruct(int n_images_to_use){
  this->parser.parse();

  vector<int> cam_to_start = Obtain_best_pair_to_start();
  Obtain_3d_points_from_pair(cam_to_start[0], cam_to_start[1]);

  int n_img_used = 2;
  while(n_img_used<n_images_to_use && n_img_used<parser.get_num_cameras()){
    int next_cam = obtain_next_best_image();
    set<int>::iterator it = cameras_used.begin();
    while (it != cameras_used.end())
    {
      Obtain_3d_points_from_pair(next_cam, *it);
    	it++;
    }
    cameras_used.insert(next_cam);
  }
}

Mat_< double > Reconstruction::Triangulation(Point2d p1, Point2d p2, Matx34d extrinsics1, Matx34d extrinsics2){
  Matx43d A(p1.x*extrinsics1(2,0)-extrinsics1(0,0),    p1.x*extrinsics1(2,1)-extrinsics1(0,1),      p1.x*extrinsics1(2,2)-extrinsics1(0,2),
            p1.y*extrinsics1(2,0)-extrinsics1(1,0),    p1.y*extrinsics1(2,1)-extrinsics1(1,1),      p1.y*extrinsics1(2,2)-extrinsics1(1,2),
            p2.x*extrinsics2(2,0)-extrinsics2(0,0),    p2.x*extrinsics2(2,1)-extrinsics2(0,1),      p2.x*extrinsics2(2,2)-extrinsics2(0,2),
            p2.y*extrinsics2(2,0)-extrinsics2(1,0),    p2.y*extrinsics2(2,1)-extrinsics2(1,1),      p2.y*extrinsics2(2,2)-extrinsics2(1,2));

  Mat_< double > B(4,1);
  B <<  -(p1.x*extrinsics1(2,3)-extrinsics1(0,3)),
        -(p1.y*extrinsics1(2,3)-extrinsics1(1,3)),
        -(p2.x*extrinsics2(2,3)-extrinsics2(0,3)),
        -(p2.y*extrinsics2(2,3)-extrinsics2(1,3));

  Mat_< double > X(3,1);
  solve(A,B,X,DECOMP_SVD);
  return X;
}

vector<int> Reconstruction::Obtain_best_pair_to_start(){
  cout<<"Start Obtain_best_pair_to_start"<<endl;
  images_to_images_common_points = vector<vector<int> >(parser.get_num_cameras(), vector<int>(parser.get_num_cameras(), 0));
  for (int i=0; i<parser.get_points().size(); ++i){
    for(int j=0; j<parser.get_points()[i].get_views().size(); ++j){
      for(int k=0; k<parser.get_points()[i].get_views().size(); ++k){
        if(k!=j){
          images_to_images_common_points[parser.get_points()[i].get_views()[j](0)][parser.get_points()[i].get_views()[k](0)] +=1;
        }
      }
    }
  }
  //Find pair of images with most points in common
  int maxElement = 0;
  int ind1 = 0;
  int ind2 = 0;
  for (int i = 0; i < images_to_images_common_points.size(); i++) {
    for (int j = 0; j < images_to_images_common_points[i].size(); j++) {
        if (images_to_images_common_points[i][j] > maxElement) {
            maxElement = images_to_images_common_points[i][j];
            ind1 = i;
            ind2 = j;
        }
    }
  }
  cameras_used.insert(ind1);
  cameras_used.insert(ind2);
  cout<<"Best pair to start: "<<ind1<<"    "<<ind2<<endl;
  vector<int> ret = vector<int>{ind1, ind2};
  return ret;
}

void Reconstruction::Obtain_3d_points_from_pair(int camera1, int camera2){
  for(int i=0; i<parser.get_camera_to_point_relation()[camera1].size(); ++i){
    int n_point = parser.get_camera_to_point_relation()[camera1][i];
    if(points3d_found.find(n_point)==points3d_found.end()){
      for(int j=0; j<parser.get_camera_to_point_relation()[camera2].size(); ++j){
        if(n_point == parser.get_camera_to_point_relation()[camera1][j]){
          bool cam1_found = false;
          bool cam2_found = false;
          Vector4d view1;
          Vector4d view2;
          for(int k; k<parser.get_points()[n_point].get_views().size(); ++k){
            if(parser.get_points()[n_point].get_views()[k](0) == camera1){
              cam1_found = true;
              view1 = parser.get_points()[n_point].get_views()[k];
            }
            if(parser.get_points()[n_point].get_views()[k](0) == camera2){
              cam2_found = true;
              view2 = parser.get_points()[n_point].get_views()[k];
            }
            if(cam1_found && cam2_found) break;
          }
          Vector2d u1;
          u1(0) = view1(2);
          u1(1) = view1(3);
          Vector2d u2;
          u2(0) = view2(2);
          u2(1) = view2(3);

          //Correct distortion
          Vector2d u1_corrected = correct_distortion(u1, parser.get_cameras()[camera1].get_k1(), parser.get_cameras()[camera1].get_k2());
          Vector2d u2_corrected = correct_distortion(u2, parser.get_cameras()[camera2].get_k1(), parser.get_cameras()[camera2].get_k2());

          //Multiply point by inverse of K
          Point3d u1_aux = Point3d(u1_corrected(0), u1_corrected(1), 1.0);
          Point3d u2_aux = Point3d(u2_corrected(0), u2_corrected(1), 1.0);

          Matx33d K1(0,0,0,
                     0,0,0,
                     0,0,0);
          K1(0,0) = parser.get_cameras()[camera1].get_focal_lenght();
          K1(1,1) = parser.get_cameras()[camera1].get_focal_lenght();
          K1(2,2) = 1.0;
          Matx33d K1_inv = K1.inv();

          u1_aux = K1_inv * u1_aux;
          Point2d u1_processed = Point2d(u1_aux.x, u1_aux.y);

          Matx33d K2(0,0,0,
                     0,0,0,
                     0,0,0);
          K2(0,0) = parser.get_cameras()[camera2].get_focal_lenght();
          K2(1,1) = parser.get_cameras()[camera2].get_focal_lenght();
          K2(2,2) = 1.0;
          Matx33d K2_inv = K2.inv();

          u2_aux = K2_inv * u2_aux;
          Point2d u2_processed = Point2d(u2_aux.x, u2_aux.y);

          //Obtain camera extrinsics
          Matx34d extr1(parser.get_cameras()[camera1].get_rotation_mat()(0,0),    parser.get_cameras()[camera1].get_rotation_mat()(0,1),      parser.get_cameras()[camera1].get_rotation_mat()(0,2),    parser.get_cameras()[camera1].get_translation_vec()(0),
                        parser.get_cameras()[camera1].get_rotation_mat()(1,0),    parser.get_cameras()[camera1].get_rotation_mat()(1,1),      parser.get_cameras()[camera1].get_rotation_mat()(1,2),    parser.get_cameras()[camera1].get_translation_vec()(1),
                        parser.get_cameras()[camera1].get_rotation_mat()(2,0),    parser.get_cameras()[camera1].get_rotation_mat()(2,1),      parser.get_cameras()[camera1].get_rotation_mat()(2,2),    parser.get_cameras()[camera1].get_translation_vec()(2));

          Matx34d extr2(parser.get_cameras()[camera2].get_rotation_mat()(0,0),    parser.get_cameras()[camera2].get_rotation_mat()(0,1),      parser.get_cameras()[camera2].get_rotation_mat()(0,2),    parser.get_cameras()[camera2].get_translation_vec()(0),
                        parser.get_cameras()[camera2].get_rotation_mat()(1,0),    parser.get_cameras()[camera2].get_rotation_mat()(1,1),      parser.get_cameras()[camera2].get_rotation_mat()(1,2),    parser.get_cameras()[camera2].get_translation_vec()(1),
                        parser.get_cameras()[camera2].get_rotation_mat()(2,0),    parser.get_cameras()[camera2].get_rotation_mat()(2,1),      parser.get_cameras()[camera2].get_rotation_mat()(2,2),    parser.get_cameras()[camera2].get_translation_vec()(2));

        //Obtain 3D point
        Mat_< double > point3d = Triangulation(u1_processed, u2_processed, extr1, extr2);

        //Store and print recovered 3D point
        Point3d col_aux(parser.get_points()[n_point].get_color()(0), parser.get_points()[n_point].get_color()(1), parser.get_points()[n_point].get_color()(2));
        Point3d p_aux(point3d(1), point3d(2), point3d(3));
        Point3D recovered_p;
        recovered_p.set_color(col_aux);
        recovered_p.set_coordinates(p_aux);
        recovered_points.push_back(recovered_p);
        recovered_p.print();
        points3d_found.insert(n_point);
        }
      }
    }
  }
}


Vector2d Reconstruction::correct_distortion(Vector2d point, float k1, float k2){
  float r = point(0)*point(0) + point(1)*point(1);
  float x_corr = point(0) * (1.0 + k1*r + k2*r*r);
  float y_corr = point(1) * (1.0 + k1*r + k2*r*r);
  Vector2d ret = Vector2d(x_corr, y_corr);
  return ret;
}

int Reconstruction::obtain_next_best_image(){
  //Obtain the image that has more point correspondances with the already chosen ones
  set<int>::iterator it = cameras_used.begin();
  vector<int> sum_appearances = images_to_images_common_points[*it];
  it++;
  while (it != cameras_used.end())
  {
  	transform (sum_appearances.begin(), sum_appearances.end(), images_to_images_common_points[*it].begin(), sum_appearances.begin(), std::plus<int>());
  	it++;
  }

  //Find the camera with more points that has not already been used
  int max_value=0;
  int index =0;
  for(int i=0; i<sum_appearances.size(); ++i){
    if(cameras_used.find(i) == cameras_used.end()){
      if(sum_appearances[i]>max_value){
        max_value = sum_appearances[i];
        index = i;
      }
    }
  }
  return index;
}
