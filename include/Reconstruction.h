#include <iostream>
#include <string>

#include "Parser.h"

using namespace std;

class Reconstruction
{
private:
  string name;
  Parser parser;
public:
  Reconstruction();
  Reconstruction(string name, string out_filename_path);
  string get_name();
  void reconstruct();
};
