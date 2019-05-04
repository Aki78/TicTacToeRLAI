//#pragma once
#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <time.h>

#include"Header/match.h"
#include"Header/players.h"
#include"Header/ann.h"


//-------------------------------------------------------
//-------------------------------------------------------
int cpyBoard(int* boardState1,int* boardState2,int boardSize){
    for(int i = 0; i < boardSize; i++){
       boardState1[i] = boardState2[i]; 
    }

}
//-------------------------------------------------------
//-------------------------------------------------------
int checkWin(int* boardState,int boardSize,int lineLength){

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
//-------------------------------------------------------
//-------------------------------------------------------
int checkState(int* boardState,int boardSize, int** states, int* currentNofS){
//printf("y1\n");
  if(currentNofS==0) return 0; 
  int returnVal = -1;
  int checkvalAccum = 0;
    for(int i = 0; i < currentNofS[0]; i++){
      checkvalAccum = 0;
      for(int j = 0; j < boardSize; j++){
        if(boardState[j] ==  states[i][j]) checkvalAccum++;
      }
//      if(checkvalAccum == boardSize)  returnVal = i;
      if(checkvalAccum == boardSize)  return i;
    }

    return returnVal;

}
//-------------------------------------------------------
//-------------------------------------------------------
int updateState(int* boardState,int boardSize, int** states, double* V, int* N, int* currentNofS, double Gt){
//printf("x6\n");

  int checkVal = 0;
  double alpha = 0.01;
 // sates init
  if(currentNofS[0] == 0){
    currentNofS[0]++;
//    states = malloc(sizeof(int*)*10000000);
    //printf("currentNoS%d\n", currentNofS[0]);
    states[0] = malloc(sizeof(int)*boardSize);
//    V = malloc(sizeof(int)*100000);
//    N = malloc(sizeof(int)*100000);
    V[0] = Gt;
    N[0] = 1;
  }
//printf("x7\n");

  if(currentNofS[0] > 0){
     checkVal = checkState( boardState, boardSize,  states, currentNofS);
//printf("x8\n");

    // if it the state doesn't exist yet
     if(checkVal <= -1){
       states[currentNofS[0]] = malloc(boardSize*sizeof(int));
       N[currentNofS[0]] = 1;
       V[currentNofS[0]] = Gt;
       for(int j = 0; j < boardSize; j++){
         states[currentNofS[0]][j] = boardState[j];
       }

       currentNofS[0]++;
     }
    // if it the state already does exist yet
      if(checkVal>=0){
         N[checkVal]++;
//         V[checkVal] += 1/(double)N[checkVal] * (Gt - V[checkVal]);
         V[checkVal] += alpha * (Gt - V[checkVal]);
      
    }
  }
}

//-------------------------------------------------------
//-------------------------------------------------------
int match(int boardSize,int P2starts,myANN* x, myANN* y){

	int lineLength=(int)sqrt(boardSize);

	short gameState = 0;
  	int *boardState = (int*)calloc(boardSize,sizeof(int));

     if (P2starts){
		//PLAYER 2 BEGINS
///		randomPlayer(boardState,boardSize,2);
		NNPlayer(boardState,boardSize,2, y);
	}

	while(1){

	//	updateBoard(boardState, boardSize, instructState, instructSize);
	//PLAYER 1	
///		randomPlayer(boardState,boardSize,1);
//		humanPlayer(boardState,lineLength,1);
		NNPlayer(boardState,boardSize,1, x);
		gameState = checkWin(boardState,boardSize,lineLength);

		if (gameState!=0) break;

	//PLAYER 2
///		randomPlayer(boardState,boardSize,2);
		NNPlayer(boardState,boardSize,2, y);
		gameState =  checkWin(boardState,boardSize,lineLength);
		if (gameState!=0) break;

	// gameState 0 = continue, 1 = first player wins, 2 = second player wins,3 = it's a draw.
	  }


		free(boardState);
		return(gameState);
}
//-------------------------------------------------------
//-------------------------------------------------------
int matchHuman(int boardSize,int P2starts, myANN* y){

	int lineLength=(int)sqrt(boardSize);

	short gameState = 0;
  	int *boardState = (int*)calloc(boardSize,sizeof(int));

     if (P2starts){
		//PLAYER 2 BEGINS
		NNPlayer(boardState,boardSize,2, y);
	}

	while(1){

	//PLAYER 1	
		humanPlayer(boardState,lineLength,1);
		gameState = checkWin(boardState,boardSize,lineLength);

		if (gameState!=0) break;

	//PLAYER 2
		NNPlayer(boardState,boardSize,2, y);
		gameState =  checkWin(boardState,boardSize,lineLength);
		if (gameState!=0) break;

	// gameState 0 = continue, 1 = first player wins, 2 = second player wins,3 = it's a draw.
	  }

		free(boardState);
		return(gameState);
}
//-------------------------------------------------------
//-------------------------------------------------------
int matchRand(int boardSize,int P2starts, myANN* x){

	int lineLength=(int)sqrt(boardSize);

	short gameState = 0;
  	int *boardState = (int*)calloc(boardSize,sizeof(int));

     if (P2starts){
		//PLAYER 2 BEGINS
///		randomPlayer(boardState,boardSize,2);
		NNPlayer(boardState,boardSize,2, x);
	}

	while(1){

	//	updateBoard(boardState, boardSize, instructState, instructSize);
	//PLAYER 1	
//        randomPlayer(boardState,boardSize,1);
//		humanPlayer(boardState,lineLength,1);
		NNPlayer(boardState,boardSize,1, x);
		gameState = checkWin(boardState,boardSize,lineLength);

		if (gameState!=0) break;

	//PLAYER 2
		randomPlayer(boardState,boardSize,2);
//		NNPlayer(boardState,boardSize,2, y);
		gameState =  checkWin(boardState,boardSize,lineLength);
		if (gameState!=0) break;

	// gameState 0 = continue, 1 = first player wins, 2 = second player wins,3 = it's a draw.
	  }


		free(boardState);
		return(gameState);
}
//-------------------------------------------------------
//-------------------------------------------------------
int matchRandMC(int boardSize,int P2starts,double* V,int* N, int** states,int* currentNofS){

//printf("x1\n");
	int lineLength=(int)sqrt(boardSize);

	short gameState = 0;
  	int *boardState = calloc(boardSize,sizeof(int));
  	int **stateBuffers = malloc(boardSize*sizeof(int*));
    for(int i = 0; i < boardSize; i++){
      stateBuffers[i] = calloc(boardSize,sizeof(int));
    }
    int playedStep = 0;

     if (P2starts){
		//PLAYER 2 BEGINS
		randomPlayer(boardState,boardSize,2);
		gameState = checkWin(boardState,boardSize,lineLength);
        cpyBoard(stateBuffers[playedStep], boardState, boardSize);
 	}

//printf("x2\n");
	while(1){

	//PLAYER 1	
        randomPlayer(boardState,boardSize,1);
		gameState = checkWin(boardState,boardSize,lineLength);
        cpyBoard(stateBuffers[playedStep], boardState, boardSize);
        playedStep++;

//printf("x3\n");
		if (gameState!=0) break;

	//PLAYER 2
		randomPlayer(boardState,boardSize,2);
		gameState = checkWin(boardState,boardSize,lineLength);
		gameState = checkWin(boardState,boardSize,lineLength);
        cpyBoard(stateBuffers[playedStep], boardState, boardSize);
        playedStep++;
		if (gameState!=0) break;

	// gameState 0 = continue, 1 = first player wins, 2 = second player wins,3 = it's a draw.
	  }
//printf("x4\n");

   if(gameState==1) {
     for(int i = 0; i < playedStep; i++){
       updateState(stateBuffers[i], boardSize,states, V, N, currentNofS, 1);
     }
   }
   if(gameState==2) {
     for(int i = 0; i < playedStep; i++){
       updateState(stateBuffers[i], boardSize,states, V, N, currentNofS, -1);
     }
   }
   if(gameState==3) {
     for(int i = 0; i < playedStep; i++){
       updateState(stateBuffers[i], boardSize,states, V, N, currentNofS, 0);
     }
   }
//printf("x5\n");


		free(boardState);
        for(int i = 0; i < boardSize; i++){
          free(stateBuffers[i]);
        }
  	    free(stateBuffers);
		return(gameState);
}
//-------------------------------------------------------
//-------------------------------------------------------
int matchRandMCDual(int boardSize,int P2starts, 
    double* V1,double* V2,
    int* N1,int*N2,
    int** states1,int**states2,
    int* currentN1,int* currentN2){

//printf("x1\n");
	int lineLength=(int)sqrt(boardSize);

	short gameState = 0;
  	int *boardState = calloc(boardSize,sizeof(int));
  	int **stateBuffers = malloc(boardSize*sizeof(int*));
    for(int i = 0; i < boardSize; i++){
      stateBuffers[i] = calloc(boardSize,sizeof(int));
    }
    int playedStep = 0;

     if (P2starts){
		//PLAYER 2 BEGINS
		randomPlayer(boardState,boardSize,2);
		gameState = checkWin(boardState,boardSize,lineLength);
        cpyBoard(stateBuffers[playedStep], boardState, boardSize);
 	}

//printf("x2\n");
	while(1){

	//PLAYER 1	
        randomPlayer(boardState,boardSize,1);
		gameState = checkWin(boardState,boardSize,lineLength);
        cpyBoard(stateBuffers[playedStep], boardState, boardSize);
        playedStep++;

//printf("x3\n");
		if (gameState!=0) break;

	//PLAYER 2
		randomPlayer(boardState,boardSize,2);
		gameState = checkWin(boardState,boardSize,lineLength);
        cpyBoard(stateBuffers[playedStep], boardState, boardSize);
        playedStep++;
		if (gameState!=0) break;

	// gameState 0 = continue, 1 = first player wins, 2 = second player wins,3 = it's a draw.
	  }
//printf("x4\n");

   if(gameState==1) {
     for(int i = 0; i < playedStep; i++){
       updateState(stateBuffers[i], boardSize,states1, V1, N1, currentN1, 1);
       updateState(stateBuffers[i], boardSize,states2, V2, N2, currentN2, -1);
//       printf("%d\n\n", states2[i][1]);
     }
   }
   if(gameState==2) {
     for(int i = 0; i < playedStep; i++){
       updateState(stateBuffers[i], boardSize,states1, V1, N1, currentN1, -1);
       updateState(stateBuffers[i], boardSize,states2, V2, N2, currentN2, 1);
     }
   }
   if(gameState==3) {
     for(int i = 0; i < playedStep; i++){
       updateState(stateBuffers[i], boardSize,states1, V1, N1, currentN1, 0);
       updateState(stateBuffers[i], boardSize,states2, V2, N2, currentN2, 0);
     }
   }
//printf("x5\n");


		free(boardState);
        for(int i = 0; i < boardSize; i++){
          free(stateBuffers[i]);
        }
  	    free(stateBuffers);
		return(gameState);
}
//-------------------------------------------------------
//-------------------------------------------------------
int matchGreedyMCDual(int boardSize,int P2starts, 
    double* V1,double* V2,
    int* N1,int*N2,
    int** states1,int**states2,
    int* currentN1,int* currentN2){

//printf("x1\n");
	int lineLength=(int)sqrt(boardSize);

	short gameState = 0;
  	int *boardState = calloc(boardSize,sizeof(int));
  	int **stateBuffers = malloc(boardSize*sizeof(int*));
    for(int i = 0; i < boardSize; i++){
      stateBuffers[i] = calloc(boardSize,sizeof(int));
    }
    int playedStep = 0;

     if (P2starts){
		//PLAYER 2 BEGINS
//		randomPlayer(boardState,boardSize,2);
        MCGreedyplayer(boardState, boardSize,2, states2,V2,  currentN2);
		gameState = checkWin(boardState,boardSize,lineLength);
        cpyBoard(stateBuffers[playedStep], boardState, boardSize);
 	}

//printf("x2\n");
	while(1){

	//PLAYER 1	
//        randomPlayer(boardState,boardSize,1);
        MCGreedyplayer(boardState, boardSize, 1, states1,V1,  currentN1);
		gameState = checkWin(boardState,boardSize,lineLength);
        cpyBoard(stateBuffers[playedStep], boardState, boardSize);
        playedStep++;

//printf("x3\n");
		if (gameState!=0) break;

	//PLAYER 2
//		randomPlayer(boardState,boardSize,2);
        MCGreedyplayer(boardState, boardSize, 2, states2,V2,  currentN2);
		gameState = checkWin(boardState,boardSize,lineLength);
        cpyBoard(stateBuffers[playedStep], boardState, boardSize);
        playedStep++;
		if (gameState!=0) break;

	// gameState 0 = continue, 1 = first player wins, 2 = second player wins,3 = it's a draw.
	  }

   if(gameState==1) {
     for(int i = 0; i < playedStep; i++){
       updateState(stateBuffers[i], boardSize,states1, V1, N1, currentN1, 1);
       updateState(stateBuffers[i], boardSize,states2, V2, N2, currentN2, -1);
//       printf("%d\n\n", states2[i][1]);
     }
   }
   if(gameState==2) {
     for(int i = 0; i < playedStep; i++){
       updateState(stateBuffers[i], boardSize,states1, V1, N1, currentN1, -1);
       updateState(stateBuffers[i], boardSize,states2, V2, N2, currentN2, 1);
     }
   }
   if(gameState==3) {
     for(int i = 0; i < playedStep; i++){
       updateState(stateBuffers[i], boardSize,states1, V1, N1, currentN1, 0);
       updateState(stateBuffers[i], boardSize,states2, V2, N2, currentN2, 0);
     }
   }
//printf("x5\n");


		free(boardState);
        for(int i = 0; i < boardSize; i++){
          free(stateBuffers[i]);
        }
  	    free(stateBuffers);
		return(gameState);
}
//-------------------------------------------------------
//-------------------------------------------------------
int matchHumanMC1(int boardSize,int P2starts,int** states, double* V, int* currentN){

	int lineLength=(int)sqrt(boardSize);

	short gameState = 0;
  	int *boardState = (int*)calloc(boardSize,sizeof(int));

     if (P2starts){
		//PLAYER 2 BEGINS
		MCplayer(boardState,boardSize,1, states, V, currentN);
	}

	while(1){

	//PLAYER 1	
		humanPlayer(boardState,lineLength,2);
		gameState = checkWin(boardState,boardSize,lineLength);

		if (gameState!=0) break;

	//PLAYER 2
		MCplayer(boardState,boardSize,1, states, V, currentN);
		gameState =  checkWin(boardState,boardSize,lineLength);
		if (gameState!=0) break;

	// gameState 0 = continue, 1 = first player wins, 2 = second player wins,3 = it's a draw.
	  }

		free(boardState);
		return(gameState);
}
//-------------------------------------------------------
//-------------------------------------------------------
int matchHumanMC2(int boardSize,int P2starts,int** states, double* V, int* currentN){

	int lineLength=(int)sqrt(boardSize);

	short gameState = 0;
  	int *boardState = (int*)calloc(boardSize,sizeof(int));

     if (P2starts){
		//PLAYER 2 BEGINS
		MCplayer(boardState,boardSize,2, states, V, currentN);
	}

	while(1){

	//PLAYER 1	
		humanPlayer(boardState,lineLength,1);
		gameState = checkWin(boardState,boardSize,lineLength);

		if (gameState!=0) break;

	//PLAYER 2
		MCplayer(boardState,boardSize,2, states, V, currentN);
		gameState =  checkWin(boardState,boardSize,lineLength);
		if (gameState!=0) break;

	// gameState 0 = continue, 1 = first player wins, 2 = second player wins,3 = it's a draw.
	  }

		free(boardState);
		return(gameState);
}
//-------------------------------------------------------
