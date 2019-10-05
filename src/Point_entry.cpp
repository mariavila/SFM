#include "Point_entry.h"

using namespace Eigen;
using namespace std;

Point_entry::Point_entry(){
}

void Point_entry::set_color(Vector3d color){
  this->color = color;
}
void Point_entry::set_views(vector<Vector4d> views){
  this->views = views;
}

Vector3d Point_entry::get_color(){
  return this->color;
}
vector<Vector4d> Point_entry::get_views(){
  return this->views;
}
