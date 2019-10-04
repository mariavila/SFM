#include "Reconstruction.h"

using namespace std;

Reconstruction::Reconstruction(){
}

Reconstruction::Reconstruction(string name, string out_filename_path){
  this->name = name;
  this->parser = Parser(out_filename_path);
}

string Reconstruction::get_name(){
  return this->name;
}

void Reconstruction::reconstruct(){
  this->parser.parse();
  cout<<parser.get_cameras()[0].get_focal_lenght()<<endl;
  cout<<parser.get_cameras()[0].get_translation_vec()<<endl;
  cout<<parser.get_cameras()[0].get_rotation_mat()<<endl;
}
