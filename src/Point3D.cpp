#include "Point3D.h"

using namespace cv;
using namespace std;

Point3D::Point3D(){
}

void Point3D::set_color(Point3d color){
  this->color = color;
}
void Point3D::set_coordinates(Point3d c){
  this->coordinates = c;
}

Point3d Point3D::get_color(){
  return this->color;
}

Point3d Point3D::get_coordinates(){
  return this->coordinates;
}

void Point3D::print(){
  cout<<"3D point"<<endl;
  cout<<"Coordinates: "<<coordinates.x<<" "<<coordinates.y<<" "<<coordinates.z<<endl;
  cout<<"Color: "<<color.x<<" "<<color.y<<" "<<color.z<<endl;
}
