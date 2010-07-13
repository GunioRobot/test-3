#include <stdio.h>

int main() {

  int   int_var[10]   = { 0, 1, 2, 3, 4, 5};
  char  char_var[10]  = "012345";

  printf("---------------------------------\n");

    if (int_var[0] == 0) {
      printf("this is a 0.\n");
    }

    if (int_var[0] == 1) {
      printf("this is a 1.\n");
    }
  
  printf("---------------------------------\n");


    if (char_var[0] == 0) {
      printf("this is a 0\n");
    }

    if (char_var[1] == 1) {
      printf("this is a 1.\n");
    }

  printf("---------------------------------\n");

  return 1; 

}
