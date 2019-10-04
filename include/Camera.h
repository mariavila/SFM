#include <iostream>
#include <string>
#include <eigen3/Eigen/Dense>

using namespace Eigen;
using namespace std;

class Camera
{
private:
  int camera_id;
  float focal_lenght;
  float k1;
  float k2;
  Matrix3f R;
  Vector3d T;

public:
  Camera(int camera_id);

  void set_rotation_mat(Matrix3f r);
  void set_translation_vec(Vector3d t);
  void set_focal_lenght(float f);
  void set_k1(float k1);
  void set_k2(float k2);

  Matrix3f get_rotation_mat();
  Vector3d get_translation_vec();
  float get_focal_lenght();
  float get_k1();
  float get_k2();
};
