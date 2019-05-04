#include <stdio.h>
#include <time.h>
#include<stdio.h>
#include <math.h> 

#include"Header/match.h"
#include"Header/ann.h"


int main(int argc, char* argv[]){
  
    myANN* p = initANN(9,2,2, 1);

    p -> bI[0] = 0.0; p -> bI[1] = 0.0;
    p -> wI[0] = 0.0; p -> wI[1] = 0.0;

    p -> bH[0] = 0.0; p -> bH[2] = 0.0;

    p -> wH[0] = 0.0; p -> wH[2] = 0.0;
    p -> wH[3] = 0.0; p -> wH[4] = 0.0;

    p -> bO[0] = 0.0; p -> bO[1] = 0.0;
    p -> wO[0] = 1.1; p -> wO[1] = -1.0;

    feedForwardNN(p);

    printf("%f\n", p -> out[0]);


  return 0;
}
