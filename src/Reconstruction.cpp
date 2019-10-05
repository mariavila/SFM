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
  /**
  vector<Vector4d> views = parser.get_points()[0].get_views();
  for(int i=0; i<views.size();++i){
    cout<<"cam: "<<views[i](0)<<endl;
  }
  cout<<"hola"<<endl;
  cout<<parser.get_camera_to_point_relation()[0][0]<<endl;
  */
}
