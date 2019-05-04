//#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include"Header/players.h"
#include"Header/ann.h"

//-------------------------------------------------------
//-------------------------------------------------------
double checkValues(int* boardState,int boardSize, int** states, int* currentNofS, double* V){
//printf("y1\n");
  
  int checkvalAccum = 0;
    for(int i = 0; i < currentNofS[0]; i++){
      checkvalAccum = 0;
      for(int j = 0; j < boardSize; j++){
        if(boardState[j] ==  states[i][j]) checkvalAccum++;
      }
      if(checkvalAccum == boardSize)  return  V[i];
    }

    printf("%s\n", "Not enough states explored.");

}
//-------------------------------------------------------
//-------------------------------------------------------
int* flipState(int* boardState,int boardSize){
//printf("y1\n");
  int* flipped = malloc(sizeof(int)*boardSize);
    for(int i = 0; i < boardSize; i++){
      flipped[i] = -boardState[i];
    }
    free(boardState);
  return flipped;

}
//-------------------------------------------------------
//-------------------------------------------------------
void flipStates(int** states,int boardSize, int* currentNofS){
    for(int i = 0; i < currentNofS[0]; i++){
      for(int j = 0; j < boardSize; j++){
        if(states[i][j]==1) states[i][j] = 2;
        if(states[i][j]==2) states[i][j] = 1;
      }
    }

}
//-------------------------------------------------------
//-------------------------------------------------------
void printBoard(int* boardState, int lineLength){
	printf("\n");
	for (int i=0;i<lineLength;i++){
		for (int j=0;j<lineLength;j++){
		printf("%d ", *(boardState+i*lineLength+j));
		}
		
		printf("\n");
	}
	printf("\n");
}

double convertInput(int x){
  if( x == 2 ) return -1.0;
  if( x == 1 ) return 1.0;
  if( x == 0 ) return 0.0;
//  else{return x;}
}

void randomPlayer(int* boardState,int boardSize,int player){
	
	while (1){
		int randomPosition=rand() % boardSize;

		if (*(boardState+randomPosition)==0) {
			*(boardState+randomPosition)=player;
			return;
		}
	}
}

//--------------------------------------------------------------
//--------------------------------------------------------------
//
//void NNPlayer(int* boardState, int boardSize, int player, myANN* x){
////   printBoard(boardState,boardSize);
//
//   int countFree = 0;
//
//   // Counting the possible states available;
//    for(int i = 0; i < boardSize; i++){
//		if (boardState[i]==0) {
//         countFree++; 
//        }
//    }
//
//   // getting the free positions;
//    int counter = 0; 
//    int* freePositions = malloc(countFree*sizeof(int));
//    for(int i = 0; i < boardSize; i++){
//      if ( boardState[i]==0 ) {
//         freePositions[counter] = i; 
//         counter++;
//      }
//    }
//
//// getting all the possible states available;
//   
//   int* decisionPlaces = malloc(boardSize*sizeof(int)*countFree);
//
//   for(int i = 0; i < countFree; i++){
//      for(int j = 0; j < boardSize ; j++){
//        decisionPlaces[i * boardSize + j] = boardState[j];// ?
//      }
//    }
//
//   for(int i = 0; i < countFree; i++){
//      for(int j = 0; j < boardSize ; j++){
//        decisionPlaces[boardSize*i + freePositions[i]] = player;// ? 3?
//      }
//    }
//
//// MDP
//   double* decisions = malloc(sizeof(double)*countFree); 
//   for(int i = 0; i < countFree; i++){
//      for(int j = 0; j < boardSize; j++){
//         x -> inp[j] = player * convertInput(decisionPlaces[boardSize*i + j]);
////         printf(":%f:\n", convertInput(decisionPlaces[boardSize*i + j]));
////         x -> inp[j] =  convertInput(decisionPlaces[boardSize*i + j]);
//      }
//
//         feedForwardNN(x);
//         decisions[i] = x -> out[0];
////         printf("%f  ",x -> out[0]);
//
//    }
////         printf("\n");
////        printBoard(boardState, boardSize);
//
//   int   getMaxIndx = 0 ;
//   double getMax = -1000000;
////   printf("free: %i\n", countFree);
//   for(int i = 0; i < countFree; i++){
//         printf("%f,", decisions[i]);
//       if(decisions[i] > getMax){
//
//         getMax = decisions[i];
//         getMaxIndx = freePositions[i];
//
//      }
//   }
//         printf("\n");
//
//   boardState[getMaxIndx] = player;
//
//   free(freePositions);
//   free(decisionPlaces);
//   free(decisions);
//
//}

//--------------------------------------------------------------
//--------------------------------------------------------------

//human player requiring inputs
void humanPlayer(int* boardState,int lineLength,int player){
	int input;
	int row;
	int column;
	int position;
	int inputOK=0;

	while(!inputOK){

		printBoard(boardState,lineLength);
		printf("Player %d make your move:\n",player);
        int input;	
//		cin >> input;
	    scanf("%d", &input);
	
		row=(input/10)-1;
		column= input%10-1;
	
		if(row >= lineLength || row<0 || column>=lineLength || column<0){
			printf("Position %d%d out of boundaries\ninsert row number and column number (i.e. 23 for row 2 and column 3)\n", row, column);
		}
		else {
			position=row*lineLength+column;
		
			if (*(boardState+position)!=0) printf("NOT valid!\nposition %d%d is already occupied by %d",row, column, *(boardState+position));
			else {
				inputOK=1;
			}
		}
	}
	*(boardState+position)=player;

}	


//--------------------------------------------------------------
//--------------------------------------------------------------

void MCplayer(int* boardState, int boardSize, int player, int** states,double* V,  int* currentN){
//   printBoard(boardState,boardSize);

   int countFree = 0;

   // Counting the possible states available;
    for(int i = 0; i < boardSize; i++){
		if (boardState[i]==0) {
         countFree++; 
        }
    }

   // getting the free positions;
    int counter = 0; 
    int* freePositions = malloc(countFree*sizeof(int));
    for(int i = 0; i < boardSize; i++){
      if ( boardState[i]==0 ) {
         freePositions[counter] = i; 
         counter++;
      }
    }

// getting all the possible states available;
   
   int* decisionPlaces = malloc(boardSize*sizeof(int)*countFree);

   for(int i = 0; i < countFree; i++){
      for(int j = 0; j < boardSize ; j++){
        decisionPlaces[i * boardSize + j] = boardState[j];// ?
      }
    }

   for(int i = 0; i < countFree; i++){
      for(int j = 0; j < boardSize ; j++){
        decisionPlaces[boardSize*i + freePositions[i]] = player;// ? 3?
      }
    }

// MDP

   double* decisions = malloc(sizeof(double)*countFree); 
   int* stateBuff= malloc(sizeof(int)*boardSize);
   
   for(int i = 0; i < countFree; i++){
       for(int j = 0; j < boardSize; j++){
          stateBuff[j] = decisionPlaces[boardSize*i + j];
       }
       decisions[i] = checkValues( stateBuff, boardSize, states, currentN, V);
   }

   int   getMaxIndx = 0 ;
   double getMax = -1000000;
//   printf("free: %i\n", countFree);
   for(int i = 0; i < countFree; i++){
         printf("%f,", decisions[i]);
       if(decisions[i] > getMax){

         getMax = decisions[i];
         getMaxIndx = freePositions[i];

      }
   }
         printf("\n");

   boardState[getMaxIndx] = player;

   free(freePositions);
   free(decisionPlaces);
   free(decisions);

}
//--------------------------------------------------------------
//--------------------------------------------------------------

void MCGreedyplayer(int* boardState, int boardSize, int player, int** states,double* V,  int* currentN){
//   printBoard(boardState,boardSize);
   double epsilon = 0.5;

   int countFree = 0;

   // Counting the possible states available;
    for(int i = 0; i < boardSize; i++){
		if (boardState[i]==0) {
         countFree++; 
        }
    }

   // getting the free positions;
    int counter = 0; 
    int* freePositions = malloc(countFree*sizeof(int));
    for(int i = 0; i < boardSize; i++){
      if ( boardState[i]==0 ) {
         freePositions[counter] = i; 
         counter++;
      }
    }

// getting all the possible states available;
   
   int* decisionPlaces = malloc(boardSize*sizeof(int)*countFree);

   for(int i = 0; i < countFree; i++){
      for(int j = 0; j < boardSize ; j++){
        decisionPlaces[i * boardSize + j] = boardState[j];// ?
      }
    }

   for(int i = 0; i < countFree; i++){
      for(int j = 0; j < boardSize ; j++){
        decisionPlaces[boardSize*i + freePositions[i]] = player;// ? 3?
      }
    }

// MDP

   double* decisions = malloc(sizeof(double)*countFree); 
   int* stateBuff= malloc(sizeof(int)*boardSize);
   
   for(int i = 0; i < countFree; i++){
       for(int j = 0; j < boardSize; j++){
          stateBuff[j] = decisionPlaces[boardSize*i + j];
       }
       decisions[i] = checkValues( stateBuff, boardSize, states, currentN, V);
   }

   int   getMaxIndx = 0 ;
   double getMax = -1000000;
//   printf("free: %i\n", countFree);
     if(simpleRand() < epsilon){
   for(int i = 0; i < countFree; i++){
     printf("%f,", decisions[i]);
       if(decisions[i] > getMax){

         getMax = decisions[i];
         getMaxIndx = freePositions[i];

       }
     }//       printf("getMax: %d\n", getMaxIndx);
     }else{
       getMaxIndx = freePositions[rand()%countFree];

   }
         printf("\n");

   boardState[getMaxIndx] = player;

   free(freePositions);
   free(decisionPlaces);
   free(decisions);

}
