#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include"playMatch.h"
#include"players.h"
#include"ann.h"

int checkWin(int* boardState,int boardSize,int lineLength){

	printBoard();

	for (int i=0;i<lineLength;i++) {
		//ROWS
		if (*(boardState+lineLength*i)!=0){	//check rows
			int j=0;
			while (1){
				j++;
				if (*(boardState+lineLength*i+j)!=*(boardState+lineLength*i+j-1)) break;
				if (j==(lineLength-1)) return *(boardState+lineLength*i+j);
				}
			}
		//COLUMNS
		if (*(boardState+i)!=0){	//check columns	
		int j=0;
			while (1){
			j++;
			if (*(boardState+i+lineLength*j)!=*(boardState+i+lineLength*(j-1))) break;
			if (j==(lineLength-1)) return *(boardState+lineLength*j+i);
		   }
		}
	}
	
	//DIAG1
	if (*boardState!=0){
	int j=0;
	while (1){
		j++;
		if (*(boardState+(lineLength+1)*j)!=*(boardState+(lineLength+1)*(j-1))) break;
		if (j==(lineLength-1)) return *boardState;
		}
	}
	
	//DIAG2
	if(*(boardState+lineLength-1)!=0){
	int j=0;
	while (1){
		j++;
		if (*(boardState+(lineLength-1)*(j+1))!=*(boardState+(lineLength-1)*j)) break;
		if (j==(lineLength-1)) return *(boardState+lineLength-1);
		}
	}

	//check if it's NOT a draw:
	for (int i=0;i<boardSize;i++) {
		if (*(boardState+i)==0) return (0);
		}
//then it's draw
	return(3);
}


int match(int boardSize,int P2starts,myANN* x){

	int lineLength=(int)sqrt(boardSize);

	short gameState = 0;
  	int *boardState = (int*)calloc(boardSize,sizeof(int));

	if (P2starts){
		//PLAYER 2 BEGINS
///		randomPlayer(boardState,boardSize,2);
		NNPlayer(boardState,boardSize,2, x);
	}

	while(1){
	//NN(boardState, boardSize, instructState, instructSize);
	//	updateBoard(boardState, boardSize, instructState, instructSize);
	//PLAYER 1	
///		randomPlayer(boardState,boardSize,1);
///		NNPlayer(boardState,boardSize,1,x);
		humanPlayer(boardState,lineLength,1);
		gameState =  checkWin(boardState,boardSize,lineLength);
		if (gameState!=0) break;

	//PLAYER 2
///		randomPlayer(boardState,boardSize,2);
		NNPlayer(boardState,boardSize,2,x);
		gameState =  checkWin(boardState,boardSize,lineLength);
		if (gameState!=0) break;

	// gameState 0 = continue, 1 = first player wins, 2 = second player wins,3 = it's a draw.
	  }


		free(boardState);
		return(gameState);
}
