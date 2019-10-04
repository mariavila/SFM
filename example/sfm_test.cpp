#include"Reconstruction.h"

int main(int argc, char *argv[]){
   Reconstruction rec("Notre Dame", "../NotreDame/notredame.out");
   cout<<rec.get_name()<<endl;
   rec.reconstruct();
   return 0;
}
