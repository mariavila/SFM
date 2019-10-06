#include <iostream>
#include <string>
#include <set>
#include <opencv2/opencv.hpp>

#include "Parser.h"
#include "Point3D.h"

using namespace std;
using namespace cv;

class Reconstruction
{
private:
  string name;
  Parser parser;
  vector<vector<int> > images_to_images_common_points;
  set<int> cameras_used;
  set<int> points3d_found;
  vector<Point3D> recovered_points;
public:
  Reconstruction();
  Reconstruction(string name, string out_filename_path);
  string get_name();
  Mat_< double > Triangulation(Point2d p1, Point2d p2, Matx34d extrinsics1, Matx34d extrinsics2);
  void reconstruct(int n_images_to_use);
  vector<int> Obtain_best_pair_to_start();
  void Obtain_3d_points_from_pair(int camera1, int camera2);
  Vector2d correct_distortion(Vector2d point, float k1, float k2);
  int obtain_next_best_image();
};
