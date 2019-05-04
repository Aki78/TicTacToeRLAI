#ifndef PLAY_MATCH   /* Include guard */
#define PLAY_MATCH

#include <stdio.h>
#include <time.h>

#include"../match.c"
#include"../players.c"
#include"../ann.c"

int cpyBoard(int* boardState1,int* boardState2,int boardSize);
int checkWin(int* boardState,int boardSize,int lineLength);
int match(int boardSize, int p2starts, myANN* x, myANN* y);
int matchRand(int boardSize,int P2starts, myANN* y);
int matchHuman(int boardSize,int P2starts, myANN* y);
int checkState(int* boardState,int boardSize, int** states, int* currentNofS);
int updateState(int* boardState,int boardSize, int** states, double* V, int* N, int* currentNofS, double Gt);
int matchRandMC(int boardSize,int P2starts,double* V,int* N, int** states,int* currentNofS);
double checkValues(int* boardState,int boardSize, int** states, int* currentNofS, double* V);
int matchHumanMC1(int boardSize,int P2starts,int** states, double* V, int* currentN);
int matchHumanMC2(int boardSize,int P2starts,int** states, double* V, int* currentN);
int matchRandMCDual(int boardSize,int P2starts, 
    double* V1,double* V2,
    int* N1,int*N2,
    int** states1,int**states2,
    int* currentN1,int* currentN2);
int matchGreedyMCDual(int boardSize,int P2starts, 
    double* V1,double* V2,
    int* N1,int*N2,
    int** states1,int**states2,
    int* currentN1,int* currentN2);



#endif 
