//#pragma once
#ifndef MY_ANN   /* Include guard */
#define MY_ANN

#include <stdio.h>
#include <time.h>

#include"../ann.c"
//#include"../players.c"

typedef struct {

  double* inp;
  int inpSize;

  double* out;
  int outSize;

  int height;
  int depth;

  double* wI;
  double* wH;
  double* wO;

  double* bI;
  double* bH;
  double* bO;
} myANN;

double myRand();

void freeNN(myANN* x);

void randomizeNN(myANN* x,double scale);
void cpyNN(myANN* x,myANN* y);

myANN* initANN(int inpSz, int height, int depth, int outSz);
myANN* mateNN(myANN* x,myANN* y, int gens);
myANN* selectRandNN(myANN** X, myANN* a,int r);

int getMaxIndx(int* a, int b);
int getMaxSndIndx(int* a, int b);

//int newNN(short* boardState,short boardSize,short* instructState, short* instructSize);
void feedForwardNN(myANN* a);
void printNN(myANN* a);
double* softMax(int* vals, int valLength, double w);
int softMaxDec(int* vals, int valLength);
double* cumsum(double* vals, int valLength);
int index_min(double* vals,int valLength, double randV);
double weightSum(myANN* a);
double simpleRand();


#endif 
