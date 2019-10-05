#include <iostream>
#include <string>
#include <eigen3/Eigen/Dense>

using namespace Eigen;
using namespace std;

class Point_entry
{
private:
  Vector3d color;
  vector<Vector4d> views;

public:
  Point_entry();

  void set_color(Vector3d color);
  void set_views(vector<Vector4d> views);

  Vector3d get_color();
  vector<Vector4d> get_views();
};
