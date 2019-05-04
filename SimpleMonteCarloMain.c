#include <stdio.h>
#include <time.h>
#include<stdio.h>
#include <math.h> 

#include"Header/match.h"
#include"Header/ann.h"


int main(int argc, char* argv[]){
    srand(time(NULL));

	short boardSize = 9;
	int matches=100;
    int d = 4;
    int h = 4;
    int popSize=10;
    int genSize=1000000;
	int switchPlayers=1;
    int result;

    int oldp1won = 1000; int oldp2won = 1000; int olddraw  = 1000;

    myANN* p1Brain = initANN(9, h, d, 1);
    myANN* p2Brain = initANN(9, h, d, 1);

    myANN* winnerBrain = initANN(9, h, d, 1);
    myANN** collectWinners = malloc(sizeof(myANN*)*popSize);

    randomizeNN(p2Brain,3.0);
    randomizeNN(p1Brain,3.0);

    int player = 0;

	int draws=0,p1won=0,p2won=0;

	srand (time(NULL));

	int P2starts=0;

  for(int gens=0; gens < genSize; gens++){ 
    for(int pops=0; pops < popSize; pops++){ 

       randomizeNN(p1Brain,3.0);

       for(int i=0; i < matches; i++) {

        randomizeNN(p2Brain,3.0);
        
        P2starts=0;
    	if (switchPlayers && i%2){ P2starts=1;}

		result = match(boardSize,P2starts,p1Brain,p2Brain);

		if (result==1) p1won++;
		if (result==2) p2won++;
		if (result==3) draws++;

      }


       if(p2won < oldp2won){
//         printf("%d\n", p2won);
         oldp2won = p2won; 
         cpyNN(winnerBrain, p1Brain);

       }

       p1won = 0;
       p2won = 0;
       draws = 0;

    }

       for(int i=0; i < matches; i++) {
         randomizeNN(p2Brain,3.0);
    	if (switchPlayers && i%2){ P2starts=1;}
        else{ P2starts=0;}

		int result=match(boardSize,P2starts,winnerBrain,p2Brain);

		if (result==1) p1won++;
		if (result==2) p2won++;
		if (result==3) draws++;

      }

	printf("Final results:\n %d",matches);
	printf(" matches played\n %d",p1won);
	printf(" matches won by Player 1\n %d",p2won);
	printf(" matches won by Player 2\n %d",draws);
	printf(" matches ended with a tie\n");
	printf("NORM: %1.3f %s %1.3f %s %1.3f \n",(double) p1won/matches," ",(double) p2won/matches," ",(double) draws/matches);

       p1won = 0;
       p2won = 0;
       draws = 0;

         printf("MaxVal:%d\n", oldp2won);
  }
// printNN(winnerBrain);
  
         printf("0:%f\n", winnerBrain->wH[0]);
         printf("0:%f\n",winnerBrain ->wH[0]);
         printf("0:%f\n",winnerBrain ->wH[0]);

    freeNN(p1Brain);
    freeNN(p2Brain);
    freeNN(winnerBrain);


     
  return 0;
}
