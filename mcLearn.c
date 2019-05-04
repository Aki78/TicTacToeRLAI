#include <stdio.h>
#include <time.h>
#include<stdio.h>
#include <math.h> 

#include"Header/match.h"


int main(int argc, char* argv[]){
    srand(time(NULL));

	short boardSize = 16;
	int matches=100000;
	int switchPlayers=1;
    int P2starts=0;
    int result;
    double* V1 = malloc(sizeof(int)*100000);
    double* V2 = malloc(sizeof(int)*100000);
    int* N1 = malloc(sizeof(int)*100000);
    int* N2 = malloc(sizeof(int)*100000);
  	int **states1 = malloc(100000*sizeof(int*));
  	int **states2 = malloc(100000*sizeof(int*));
    int p1won=0;
    int p2won=0;
    int draws=0;
    int* current1 = malloc(sizeof(int)*1);
    int* current2 = malloc(sizeof(int)*1);

      for(int i=0; i < matches; i++){
//         if (switchPlayers && i%2){ P2starts=1;}
//         else{ P2starts=0;}
//		 result=matchRandMC(boardSize,P2starts,V, N ,states, current);
		 result = matchRandMCDual(boardSize,P2starts,
                                    V1,V2, N1, N2,
                                    states1,states2,
                                    current1, current2);
//printf("x\n");
		 if (result==1) p1won++;
         if (result==2) p2won++;
         if (result==3) draws++;
	//printf("results: %d\n",result);

      }

//      MCplayer( boardState,  boardSize,  1,  states, V,  N,  current);

//      wonNum[pops] = p1won - p2won - (int)floor(100*weightSum(Brains[pops]));
        
//      p1won = 0;
//      p2won = 0;
//      draws = 0;


	printf("Final results: %d\n",matches);
	printf(" matches played %d\n",p1won);
	printf(" matches won by Player 1 %d\n",p2won);
	printf(" matches won by Player 2 %d\n",draws);
//	printf(" matches ended with a tie\n");
//	printf("NORM: %1.3f %s %1.3f %s %1.3f \n",(double) p1won/matches," ",(double) p2won/matches," ",(double) draws/matches);
    for(int i = 0; i < current1[0] ; i++){
        printf("(1) %f ", V1[i]);  printf("%d ", N1[i]);
           for(int j = 0; j < boardSize; j++){
               if(j%4==0) printf("\n");
               printf("%d ", states1[i][j]) ;
           }
           printf("\n");
    }
    for(int i = 0; i < current2[0] ; i++){
        printf("(2) %f ", V2[i]);  printf("%d ", N2[i]);
           for(int j = 0; j < boardSize; j++){
               if(j%4==0) printf("\n");
               printf("%d ", states2[i][j]) ;
           }
           printf("\n");
    }
        printf("%d ", current1[0]);
        printf("%d ", current2[0]);
    for(int i = 0; i < 1000; i++){
//         if (switchPlayers && i%2){ P2starts=1;}
//         else{ P2starts=0;}
//       if(P2starts == 0) matchHumanMC(boardSize, P2starts, states1,  V1,  current1);
          matchHumanMC1(boardSize, 1, states1,  V1,  current1);
          matchHumanMC2(boardSize, 0, states2,  V2,  current2);
    }
  return 0;
}
