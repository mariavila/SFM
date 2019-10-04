#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <eigen3/Eigen/Dense>

#include "Camera.h"

using namespace std;
using namespace Eigen;

class Parser
{
private:
  string filename_path;
  int num_cameras;
  int num_points;
  vector<Camera> cameras;
  //List<Point_entry> points;

public:
  Parser();
  Parser(string filename);
  void parse();
  vector<Camera> get_cameras();
};
