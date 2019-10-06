#include "Parser.h"

using namespace std;

Parser::Parser(){
}

Parser::Parser(string filename){
  this->filename_path = filename;
}


vector<Camera> Parser::get_cameras(){
  return this->cameras;
}


vector<Point_entry> Parser::get_points(){
  return this->points;
}
vector<vector<int> > Parser::get_camera_to_point_relation(){
  return this->camera_to_point_relation;
}

int Parser::get_num_cameras(){
  return this->num_cameras;
}

void Parser::parse(){
  ifstream file(this->filename_path.c_str());
  if(file.is_open()){
    string line, aux;
    getline(file, line);
    getline(file, line);
    istringstream iss(line);
    iss>>aux;
    this->num_cameras = stoi(aux);
    this->cameras = vector<Camera>(this->num_cameras);
    this->camera_to_point_relation = vector<vector<int> >(this->num_cameras);
    iss>>aux;
    this->num_points = stoi(aux);
    this->points = vector<Point_entry>(this->num_points);

    for(int i = 0; i<num_cameras; ++i){
      Camera cam;
      getline(file, line);
      iss = istringstream(line);
      //Set intrinsic parameters
      iss>>aux;
      cam.set_focal_lenght(stof(aux));
      iss>>aux;
      cam.set_k1(stof(aux));
      iss>>aux;
      cam.set_k2(stof(aux));

      //Set rotation matrix
      Matrix3f rot;
      getline(file, line);
      iss = istringstream(line);
      iss>>aux;
      rot(0,0) = stof(aux);
      iss>>aux;
      rot(0,1) = stof(aux);
      iss>>aux;
      rot(0,2) = stof(aux);

      getline(file, line);
      iss = istringstream(line);
      iss>>aux;
      rot(1,0) = stof(aux);
      iss>>aux;
      rot(1,1) = stof(aux);
      iss>>aux;
      rot(1,2) = stof(aux);

      getline(file, line);
      iss = istringstream(line);
      iss>>aux;
      rot(2,0) = stof(aux);
      iss>>aux;
      rot(2,1) = stof(aux);
      iss>>aux;
      rot(2,2) = stof(aux);

      cam.set_rotation_mat(rot);

      //Set translation matrix
      Vector3d trans;
      getline(file, line);
      iss = istringstream(line);
      iss>>aux;
      trans(0) = stof(aux);
      iss>>aux;
      trans(1) = stof(aux);
      iss>>aux;
      trans(2) = stof(aux);

      cam.set_translation_vec(trans);

      this->cameras[i] = cam;
    }
    for(int i = 0; i<num_points; ++i){
      Point_entry p;
      getline(file, line);

      //Set the color
      Vector3d col;
      getline(file, line);
      iss = istringstream(line);
      iss>>aux;
      col(0) = stoi(aux);
      iss>>aux;
      col(1) = stoi(aux);
      iss>>aux;
      col(2) = stoi(aux);
      p.set_color(col);

      //Set the view list
      getline(file, line);
      iss = istringstream(line);
      iss>>aux;
      int num_cameras_point_visible = stoi(aux);
      vector<Vector4d> views = vector<Vector4d>(num_cameras_point_visible);
      for(int j=0; j<num_cameras_point_visible; j++){
        Vector4d loc_cam_info;
        iss>>aux;
        loc_cam_info(0) = stoi(aux);
        this->camera_to_point_relation[stoi(aux)].push_back(i);
        iss>>aux;
        loc_cam_info(1) = stoi(aux);
        iss>>aux;
        loc_cam_info(2) = stof(aux);
        iss>>aux;
        loc_cam_info(3) = stof(aux);
        views[j] = loc_cam_info;
      }
      p.set_views(views);

      this->points[i] = p;
    }
  }
}
