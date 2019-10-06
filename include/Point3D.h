#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class Point3D
{
private:
  Point3d color;
  Point3d coordinates;

public:
  Point3D();

  void set_color(Point3d color);
  void set_coordinates(Point3d c);

  Point3d get_color();
  Point3d get_coordinates();
  void print();
};
