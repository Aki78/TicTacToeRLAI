//#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h> /* memset */
#include <unistd.h> /* close */

#include"Header/ann.h"
//---------------------------------------------------------
//---------------------------------------------------------
double myRand(double scale){
      return scale*(-1.0 + 2.0 * (double)rand() / (double)RAND_MAX) ;
}
//---------------------------------------------------------
//---------------------------------------------------------
int index_min(double* vals,int valLength, double randV){

  double minVal = 1234567.0;
  int minIndx =12345678;

       for(int i = 0; i < valLength; i++){
         if(fabs(vals[i] - randV) < minVal){
           minVal = fabs(vals[i] - randV);
           minIndx = i;
//      printf("minIndx:%f\n", minVal);
         }
           
//           printf("minIndx:%f\n",fabs(vals[i] - randV));
       }

  return minIndx;
      
}
//---------------------------------------------------------
//---------------------------------------------------------
double simpleRand(){
      return  (double)rand() / (double)RAND_MAX ;
}
//---------------------------------------------------------
//---------------------------------------------------------
double* softMax(int* vals, int valLength, double w){
  double* y = malloc(sizeof(double)*valLength);
  double sum = 0;
  for(int i = 0; i < valLength; i++){
      sum = 0;
    for(int j = 0; j < valLength; j++){
      sum+=exp(w*(double)vals[j]);
    }
//      printf("sum:%f\n", sum);
      y[i] = exp(w*(double)vals[i])/sum;
  }
    for(int i = 0; i < valLength; i++){
//         printf("vals:%f\n", (double)vals[i]);
    }
    for(int i = 0; i < valLength; i++){
//         printf("y:%f\n", y[i]);
    }
  return y;
}
//---------------------------------------------------------
//---------------------------------------------------------
double* cumsum(double* vals, int valLength){
  double* z = malloc(sizeof(double)*valLength);
  double sum = 0;
  for(int i = 0; i < valLength; i++){

      z[i] = vals[i] + sum;
      sum = z[i];

  }
    for(int i = 0; i < valLength; i++){
//         printf("z:%f\n", z[i]);
    }
  return z;
}
//---------------------------------------------------------
//---------------------------------------------------------
int softMaxDec(int* vals, int valLength){

        double* y = softMax(vals, valLength,0.01);
        double* z = cumsum(y, valLength); 
        double prop = (double)(rand() )/(RAND_MAX);
//        myindex = index_min(abs(z - (double)(rand() + 1)/(RAND_MAX))  );
//        printf("%d\n",index_min(z,valLength,prop));
           for(int i = 0; i < valLength; i++){
//             printf("f:%f\n",z[i]);
             if(prop < z[i]) return i;
        
           }
//        return index_min(z,valLength,prop);

//        for(int j=0;j < valLength; j++){
//		if( prop > z[j]) return j;  // FIX!! Select the index by probability distribution.
//	  }

//        return valLength - 1;
}
//---------------------------------------------------------
double sigmoid(double x)
{
     return 1 / (1 + exp(-x));
}
//---------------------------------------------------------
//---------------------------------------------------------
myANN* initANN(int inpSz, int h, int d, int outSz){

  myANN *a = malloc(sizeof(myANN));

  a -> inp = malloc(sizeof(double)*inpSz);
  
  a -> inpSize = inpSz;

  a -> height = h;
  a -> depth = d;

  a -> out = malloc(sizeof(double)*outSz);
  a -> outSize = outSz;

  a -> wI = malloc(sizeof(double)*h*(a->inpSize));
  a -> wH = malloc(sizeof(double)*h*h*(d - 1));

  a -> wO = malloc(sizeof(double)*h*outSz);

  a -> bI = malloc(sizeof(double)*h);
  a -> bH = malloc(sizeof(double)*h*(d-1));
  a -> bO = malloc(sizeof(double)*outSz);
  return a;
}

//--------------------------------------------------
//--------------------------------------------------

void freeNN(myANN* a){

  free(a -> inp);
  
  free(a -> out);

  free(a -> wI);
  free(a -> wH);

  free(a -> wO);

  free(a -> bI);
  free(a -> bH);
  free(a -> bO);

  free(a);
}

//--------------------------------------------------
//--------------------------------------------------
void feedForwardNN(myANN* a){

 
   int wISize = a -> height * (a->inpSize);
   double* Llayer = malloc((a -> height)*sizeof(double));
//   double* Llayer = calloc(3,sizeof(double));
   double* buffLayer = malloc(sizeof(double)*(a -> height));
   
 //----- IN -----------------------------------------    

     memset(Llayer, 0.0, sizeof(double)*(a -> height));
     memset(buffLayer, 0.0,sizeof(double)*(a -> height));

     int weightMarch = 0;
     int layerMarch = 0;

     double buffVal = 0.0;
     for(int i = 0; i < a -> height ; i++){ 
       buffVal = 0.0;
       for(int j = 0; j < a -> inpSize ; j++){

//         buffLayer[i] = buffLayer[i] + (a -> wI[weightMarch]) * (a -> inp[j]);
         buffVal = buffVal + (a -> wI[weightMarch]) * (a -> inp[j]);
         weightMarch++;

       }

//       Llayer[i] = sigmoid(buffLayer[i] + a -> bI[i]);
       Llayer[i] = tanh(buffVal + a -> bI[i]);
//       Llayer[i] = buffVal + a -> bI[i];

     }


  //----- HIDDEN --------------------------------------
if(a -> depth > 1){

   weightMarch = 0;
   layerMarch = 0;

 for(int eachL = 0; eachL < a -> depth - 1 ; eachL++){

   memset(buffLayer, 0.0, (a -> height)*sizeof(double) );
//   memset(Llayer, 0.0, (a -> height)*sizeof(double) ); // Wrong but used for testing.
   

   for(int i = 0; i < a -> height ; i++){
     buffVal = 0.0;
     for(int j = 0; j < a -> height ; j++){

         buffLayer[i] = buffLayer[i] + a -> wH[weightMarch] * Llayer[j] ;
         weightMarch++;

     }
   }

   for(int i = 0; i < a -> height ; i++){

       Llayer[i] = tanh(buffLayer[i] + a -> bH[layerMarch]);
//       Llayer[i] = buffLayer[i] + a -> bH[layerMarch];
       layerMarch++;

   }

 }

}


 //----- OUT -----------------------------------------    
 
   weightMarch = 0;
   memset(buffLayer, 0.0, sizeof(double)*(a -> height));

   for(int i = 0; i < a -> outSize ; i++){
     buffVal = 0;
     for(int j = 0; j < a -> height ; j++){

//        buffLayer[i] = buffLayer[i] + a -> wO[weightMarch] * Llayer[j];
        buffVal = buffVal + a -> wO[weightMarch] * Llayer[j];
        weightMarch++;

       }
       a -> out[i] = tanh(buffLayer[i]+ a -> bO[i]);
//       a -> out[i] = buffVal + a -> bO[i]; // Erased Sigmoid
     }

 free(Llayer);
 free(buffLayer);

}

//---------------------------------------------------------------
//---------------------------------------------------------------

void randomizeNN(myANN* a, double scale){

  int h = a -> height; int d = a -> depth; int iS =  a -> inpSize; int oS = a -> outSize;
  double* wI = a -> wI; double* wH = a -> wH; double* wO = a -> wO;
  double* bI = a -> bI; double* bH = a -> bH; double* bO =  a -> bO;
  
// randomize Input weights
  int weightMarch = 0;

  for(int i = 0; i < h ; i++){
    bI[i] = myRand(scale);
  }

   for(int i = 0; i < h ; i++){ 
     for(int j = 0; j < iS ; j++){

       wI[weightMarch] = myRand(scale);
       weightMarch++;

   }
 }

// randomize Hidden weights
if(d > 1){
  weightMarch = 0;

  for(int i = 0; i < (d-1)*h ; i++){
    bH[i] = myRand(scale);
  }

  for(int eachL = 0; eachL < (d-1)  ; eachL++){
    for(int i = 0; i < h; i++){
      for(int j = 0; j < h; j++){

        wH[weightMarch] = myRand(scale);
        weightMarch++;

      }
    }
  }
}

// randomize Output weights
  weightMarch = 0;
  for(int i = 0; i < oS ; i++){
    bO[i] = myRand(scale);
  }

 for(int i = 0; i < oS ; i++){
   for(int j = 0; j < h; j++){
      wO[weightMarch] = myRand(scale);
      weightMarch++;
     }
   }


}

//---------------------------------------------------------------
//---------------------------------------------------------------

void cpyNN(myANN* a, myANN* b){

  int h = a -> height; int d = a -> depth; int iS =  a -> inpSize; int oS = a -> outSize;
  double* wIa = a -> wI; double* wHa = a -> wH; double* wOa = a -> wO;
  double* bIa = a -> bI; double* bHa = a -> bH; double* bOa =  a -> bO;
  double* wIb = b -> wI; double* wHb = b -> wH; double* wOb = b -> wO;
  double* bIb = b -> bI; double* bHb = b -> bH; double* bOb =  b -> bO;
  
// cp Input weights
  int weightMarch = 0;

  for(int i = 0; i < h ; i++){
    bIa[i] = bIb[i];
  }

   for(int i = 0; i < h ; i++){ 
     for(int j = 0; j < iS ; j++){

       wIa[weightMarch] = wIb[weightMarch];
       weightMarch++;

   }
 }

// cp Hidden weights
  weightMarch = 0;
if(d > 1){
  for(int i = 0; i < (d-1)*h ; i++){
    bHa[i] = bHb[i];
  }

  for(int eachL = 0; eachL < (d-1)  ; eachL++){
    for(int i = 0; i < h; i++){
      for(int j = 0; j < h; j++){

        wHa[weightMarch] = wHb[weightMarch];
        weightMarch++;

      }
    }
  }
}

// randomize Output weights
  weightMarch = 0;
  for(int i = 0; i < oS ; i++){
    bOa[i] = bOb[i];
  }

 for(int i = 0; i < oS ; i++){
   for(int j = 0; j < h; j++){
      wOa[weightMarch] = wOb[weightMarch];
      weightMarch++;
     }
   }


}

//---------------------------------------------------------------
//---------------------------------------------------------------

void printNN(myANN* a){

  FILE *fp;
  fp = fopen("test", "a");

  int h = a -> height; int d = a -> depth; int iS = a -> inpSize; int oS = a -> outSize;
  double* wIa = a -> wI; double* wHa = a -> wH; double* wOa = a -> wO;
  double* bIa = a -> bI; double* bHa = a -> bH; double* bOa =  a -> bO;
  
// cp Input weights
  int weightMarch = 0;

  for(int i = 0; i < h ; i++){
   fwrite( bIa + i, 1, sizeof(double), fp ); 
  }

   for(int i = 0; i < h ; i++){ 
     for(int j = 0; j < iS ; j++){

       fwrite(wIa+weightMarch, 1, sizeof(double), fp ); 
       weightMarch++;

   }
 }

// cp Hidden weights
  weightMarch = 0;

  for(int i = 0; i < (d-1)*h ; i++){
    fwrite(bHa+i, 1, sizeof(double), fp ); 
  }

  for(int eachL = 0; eachL < (d-1)  ; eachL++){
    for(int i = 0; i < h; i++){
      for(int j = 0; j < h; j++){

        fwrite(wHa+weightMarch, 1, sizeof(double), fp ); 
        weightMarch++;

      }
    }
  }

// randomize Output weights
  weightMarch = 0;
  for(int i = 0; i < oS ; i++){
        fwrite(bOa+i, 1, sizeof(double), fp ); 
  }

 for(int i = 0; i < oS ; i++){
   for(int j = 0; j < h; j++){
       fwrite(wOa+weightMarch, 1, sizeof(double), fp ); 
       weightMarch++;
     }
   }


}

//---------------------------------------------------------------
//---------------------------------------------------------------
myANN* mateNN(myANN* a, myANN* b, int gens){
    double backGround = 0.01;
    double nuclear = 0.1;

  myANN* c = initANN(a -> inpSize, a -> height, a -> depth, a -> outSize);
//  printf("a\n");

  int h = a -> height; int d = a -> depth; int iS =  a -> inpSize; int oS = a -> outSize;

  double* wIa = a -> wI; double* wHa = a -> wH; double* wOa = a -> wO;
  double* bIa = a -> bI; double* bHa = a -> bH; double* bOa =  a -> bO;

  double* wIb = b -> wI; double* wHb = b -> wH; double* wOb = b -> wO;
  double* bIb = b -> bI; double* bHb = b -> bH; double* bOb =  b -> bO;
  
  double* wIc = c -> wI; double* wHc = c -> wH; double* wOc = c -> wO;
  double* bIc = c -> bI; double* bHc = c -> bH; double* bOc =  c -> bO;

  int weightMarch = 0;
  double  randVal = 0;

  for(int i = 0; i < h ; i++){
    randVal = myRand(1.0);
//    printf("%f\nxyz",randVal);
    if(randVal > 0.0) bIc[i] = bIa[i] + myRand(backGround);
    if(randVal <= 0.0) bIc[i] = bIb[i] + myRand(backGround);
    if(simpleRand() < nuclear) bIc[i] += myRand(1.0);
  }

   for(int i = 0; i < h ; i++){ 
     for(int j = 0; j < iS ; j++){
       randVal = myRand(1.0);
       if(randVal > 0.0) wIc[weightMarch] = wIa[weightMarch] + myRand(backGround);
       if(randVal <= 0.0) wIc[weightMarch] = wIb[weightMarch] + myRand(backGround);
       if(simpleRand() < nuclear) wIc[weightMarch] += myRand(1.0);

       weightMarch++;

   }
 }

  weightMarch = 0;

  for(int i = 0; i < (d-1)*h ; i++){
    randVal = myRand(1.0);
    if(randVal > 0.0) bHc[i] = bHa[i] + myRand(backGround);
    if(randVal <= 0.0) bHc[i] = bHb[i] + myRand(backGround);
    if(simpleRand() < nuclear) bHc[i] += myRand(1.0);
  }

  for(int eachL = 0; eachL < (d-1)  ; eachL++){
    for(int i = 0; i < h; i++){
      for(int j = 0; j < h; j++){
        randVal = myRand(1.0);
        if(randVal > 0.0)wHc[weightMarch] = wHa[weightMarch] + myRand(backGround);
        if(randVal <= 0.0)wHc[weightMarch] = wHb[weightMarch] + myRand(backGround);
        if(simpleRand() < nuclear) wHc[weightMarch] += myRand(1.0);
        weightMarch++;
      }
    }
  }

  weightMarch = 0;
  for(int i = 0; i < oS ; i++){

    randVal = myRand(1.0);
    if(randVal > 0.0) bOc[i] = bOa[i] + myRand(backGround);
    if(randVal <= 0.0) bOc[i] = bOb[i] + myRand(backGround);
    if(simpleRand() < nuclear) bOc[i] += myRand(1.0);

  }

 for(int i = 0; i < oS ; i++){
   for(int j = 0; j < h; j++){
      randVal = myRand(1.0);
      if(randVal > 0.0)wOc[weightMarch] = wOa[weightMarch] + myRand(backGround);
      if(randVal <= 0.0)wOc[weightMarch] = wOb[weightMarch] + myRand(backGround);
      if(simpleRand() < nuclear) wOc[i] += myRand(1.0);
      weightMarch++;
     }
   }

//printf("%f yyy\n", c -> wI[1]);
 return c;

}

//---------------------------------------------------------------
//---------------------------------------------------------------

myANN* selectRandNN(myANN** A, myANN* a, int popSize){
  myANN* newC = initANN(a -> inpSize, a -> height, a -> depth, a -> outSize);
  int r = rand() % popSize;
  cpyNN(newC, A[r]);
//  printf("%f xxx\n", newC -> wI[1]);

  return newC;
}

//---------------------------------------------------------------
//---------------------------------------------------------------

int getMaxIndx(int* a,int popSize){
     int maxInx = -1;
     int maxVal = -10000;
     for(int i = 0; i < popSize ; i++){
       if(maxVal < a[i] ){maxInx = i; maxVal = a[i];}  
     }
  return maxInx;
}

//---------------------------------------------------------------
//---------------------------------------------------------------

int getMaxSndIndx(int* a,int popSize){
     int maxInx = -1;
     int maxVal = -10000;
     int sndVal = -10000;
     for(int i = 0; i <popSize ; i++){
       if(maxVal < a[i] ){maxInx = i; maxVal = a[i];}  
     }
     for(int i = 0; i <popSize ; i++){
       if(sndVal < a[i] && a[i] != maxVal){maxInx = i; sndVal = a[i];}  
     }
  return maxInx;
}

//---------------------------------------------------------------
//---------------------------------------------------------------
double weightSum(myANN* a){
  myANN* c = initANN(a -> inpSize, a -> height, a -> depth, a -> outSize);
//  printf("a\n");

  int h = a -> height; int d = a -> depth; int iS =  a -> inpSize; int oS = a -> outSize;

  double* wIa = a -> wI; double* wHa = a -> wH; double* wOa = a -> wO;
  double* bIa = a -> bI; double* bHa = a -> bH; double* bOa =  a -> bO;

  double  sum = 0;
  int weightMarch = 0;

  for(int i = 0; i < h ; i++){
     sum +=fabs(bIa[i]);
  }

   for(int i = 0; i < h ; i++){ 
     for(int j = 0; j < iS ; j++){
       sum+=fabs(wIa[weightMarch]); 
       weightMarch++;
   }
 }

  weightMarch = 0;

  for(int i = 0; i < (d-1)*h ; i++){
     sum += fabs(bHa[i]);
  }

  for(int eachL = 0; eachL < (d-1)  ; eachL++){
    for(int i = 0; i < h; i++){
      for(int j = 0; j < h; j++){
         sum += fabs(wHa[weightMarch]);
         weightMarch++;
      }
    }
  }

  weightMarch = 0;
  for(int i = 0; i < oS ; i++){

     sum += fabs(bOa[i]);

  }

 for(int i = 0; i < oS ; i++){
   for(int j = 0; j < h; j++){
      sum += fabs(wOa[weightMarch]);
      weightMarch++;
     }
   }

//printf("%f yyy\n", c -> wI[1]);
 return sum;

}

//---------------------------------------------------------------
