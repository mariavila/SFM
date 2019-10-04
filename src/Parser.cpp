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
    iss>>aux;
    this->num_points = stoi(aux);

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
  }
}
