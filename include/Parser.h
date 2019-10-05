#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <eigen3/Eigen/Dense>

#include "Camera.h"
#include "Point_entry.h"

using namespace std;
using namespace Eigen;

class Parser
{
private:
  string filename_path;
  int num_cameras;
  int num_points;
  vector<Camera> cameras;
  vector<Point_entry> points;
  vector<vector<int> > camera_to_point_relation;

public:
  Parser();
  Parser(string filename);
  void parse();
  vector<Camera> get_cameras();
  vector<Point_entry> get_points();
  vector<vector<int> > get_camera_to_point_relation();
};
