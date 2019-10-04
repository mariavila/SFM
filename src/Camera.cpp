#include "Camera.h"

using namespace Eigen;
using namespace std;

Camera::Camera(int camera_id){
  this->camera_id = camera_id;
}

void Camera::set_rotation_mat(Matrix3f r){
  this->R = r;
}

void Camera::set_translation_vec(Vector3d t){
  this->T = t;
}

void Camera::set_focal_lenght(float f){
  this->focal_lenght = f;
}

void Camera::set_k1(float k1){
  this->k1 = k1;
}

void Camera::set_k2(float k2){
 this->k2 = k2;
}


Matrix3f Camera::get_rotation_mat(){
  return this->R;
}

Vector3d Camera::get_translation_vec(){
  return this->T;
}

float Camera::get_focal_lenght(){
 return this->focal_lenght;
}

float Camera::get_k1(){
  return this->k1;
}

float Camera::get_k2(){
  return this->k2;
}
