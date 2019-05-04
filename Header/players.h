#ifndef STUPID_PLAYER   /* Include guard */
#define STUPID_PLAYER

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include"../players.c"
//#include"../ann.c"

void printBoard(int* boardState, int boardSize);
void randomPlayer(int* boardState,int boardSize,int player);
void NNPlayer(int* boardState,int boardSize,int player,myANN* x);
void humanPlayer(int* boardState,int boardSize,int player);
void MCplayer(int* boardState, int boardSize, int player, int** states,double* V,  int* currentN);
int* flipState(int* boardState,int boardSize);
void flipStates(int** states,int boardSize, int* currentNofS);
void MCGreedyplayer(int* boardState, int boardSize, int player, int** states,double* V,  int* currentN);
//double checkValues(int* boardState,int boardSize, int** states, int* currentNofS, double* V);


#endif 
