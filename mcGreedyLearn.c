#include <stdio.h>
#include <time.h>
#include <stdio.h>
#include <math.h> 

#include"Header/match.h"

int main(){
    printf("Hi\n");
    srand(time(NULL));

	short boardSize = 9;
	int matches = 1000000;
	int switchPlayers = 1;
    int memallocSize = 100000;
    int P2starts = 0;
    int result;
    double* V1 = malloc(sizeof(int)*memallocSize);
    double* V2 = malloc(sizeof(int)*memallocSize);
    int* N1 = malloc(sizeof(int)*memallocSize);
    int* N2 = malloc(sizeof(int)*memallocSize);
  	int **states1 = malloc(memallocSize*sizeof(int*));
  	int **states2 = malloc(memallocSize*sizeof(int*));
    int p1won=0;
    int p2won=0;
    int draws=0;
    int* current1 = malloc(sizeof(int));
    int* current2 = malloc(sizeof(int));

    for(int i=0; i < matches; i++){
      printf("%d\n",i);
      result = matchGreedyMCDual(boardSize,P2starts,
                                    V1,V2, N1, N2,
                                    states1,states2,
                                    current1, current2);
      if (result==1) p1won++;
      if (result==2) p2won++;
      if (result==3) draws++;

      }

	printf("Final results: %d",matches);
	printf(" matches played %d",p1won);
	printf(" matches won by Player 1 %d",p2won);
	printf(" matches won by Player 2 %d",draws);

    for(int i = 0; i < current1[0] ; i++){
        printf("(1) %f ", V1[i]);  printf("%d ", N1[i]);
           for(int j = 0; j < boardSize; j++){
               if(j%3==0) printf("\n");
               printf("%d ", states1[i][j]) ;
           }
           printf("\n");
    }
    for(int i = 0; i < current2[0] ; i++){
        printf("(2) %f ", V2[i]);  printf("%d ", N2[i]);
           for(int j = 0; j < boardSize; j++){
               if(j%3==0) printf("\n");
               printf("%d ", states2[i][j]) ;
           }
           printf("\n");
    }
        printf("%d ", current1[0]);
        printf("%d ", current2[0]);
    for(int i = 0; i < 1000; i++){
          matchHumanMC1(boardSize, 0, states1,  V1,  current1);
          matchHumanMC2(boardSize, 1, states2,  V2,  current2);
    }
  return 0;
}
