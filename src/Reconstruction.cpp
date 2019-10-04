#include "Reconstruction.h"

using namespace std;

Reconstruction::Reconstruction(string name){
  this->name = name;
}

string Reconstruction::get_name(){
  return this->name;
}
