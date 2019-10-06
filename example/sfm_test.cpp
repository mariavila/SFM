#include"Reconstruction.h"

int main(int argc, char *argv[]){
   Reconstruction rec("Notre Dame", "../NotreDame/notredame.out");
   int number_images_to_take_into_account = 5;
   rec.reconstruct(number_images_to_take_into_account);
   return 0;
}
