#include <stdio.h>
#include <time.h>
#include<stdio.h>
#include <math.h> 

#include"Header/match.h"
#include"Header/ann.h"


int main(int argc, char* argv[]){
    srand(time(NULL));

	short boardSize = 9;
	int matches=1000;
    int d = 5;
    int h = 5;
    int popSize=10;
    int genSize=100000;
	int switchPlayers=1;
    int result;
    int winning = -100000;

    int oldp1won = 100000; int oldp2won = 100000; int olddraw  = 100000;

    myANN* p1Brain = initANN(9, h, d, 1);
    myANN* p2Brain = initANN(9, h, d, 1);
    myANN* buff1Brain = initANN(9, h, d, 1);
    myANN* buff2Brain = initANN(9, h, d, 1);
    myANN* winnerBrain = initANN(9, h, d, 1);

    myANN** Brains = malloc(sizeof(myANN*)*popSize);
    myANN** BabyBrains = malloc(sizeof(myANN*)*popSize);

    int* wonNum = malloc(sizeof(int)*popSize);

    for(int i = 0; i < popSize; i++){
    
      Brains[i] =  initANN(9, h, d, 1);
      BabyBrains[i] =initANN(9, h, d, 1);
        
    }
    for(int i = 0; i < popSize; i++){
    
      randomizeNN(Brains[i],0.0);
        
    }

    randomizeNN(p2Brain,1.0);
    randomizeNN(p1Brain,1.0);

    int player = 0;
	int draws=0,p1won=0,p2won=0;

	srand(time(NULL));

	int P2starts=0;

       randomizeNN(p2Brain,1.0);
       randomizeNN(p1Brain,1.0);
    for(int gens=0; gens < genSize; gens++){ 

      cpyNN(buff1Brain,Brains[getMaxIndx(wonNum,popSize)]);
      cpyNN(buff2Brain,Brains[getMaxSndIndx(wonNum,popSize)]);
      cpyNN(p1Brain, mateNN(buff1Brain, buff2Brain, gens));
      cpyNN(buff1Brain,Brains[getMaxIndx(wonNum,popSize)]);
      cpyNN(buff2Brain,Brains[getMaxSndIndx(wonNum,popSize)]);
      cpyNN(p2Brain, mateNN(buff1Brain, buff2Brain, gens));

      for(int pops=0; pops < popSize; pops++){ 

       for(int i=0; i < matches; i++){
         if (switchPlayers && i%2){ P2starts=1;}
         else{ P2starts=0;}
//         randomizeNN(p2Brain,1.0); 
//		 result=match(boardSize,P2starts,p1Brain,p2Brain);
		 result=matchRand(boardSize,P2starts,p1Brain);

		 if (result==1) p1won++;
         if (result==2) p2won++;
         if (result==3) draws++;

      }


//         result = match(boardSize, P2starts, p1Brain, p2Brain);
         result = matchRand(boardSize, P2starts, p1Brain);
        
         if(p1won > p2won ){wonNum[pops] = p1won; cpyNN(BabyBrains[pops],  p1Brain);}
//         if(p1won < p2won ){wonNum[pops] = p2won; cpyNN(BabyBrains[pops],  p2Brain);}

       p1won = 0;
       p2won = 0;
       draws = 0;
    }

    for(int i = 0; i < popSize; i++){
       cpyNN(Brains[i], BabyBrains[i]);
    }

    for(int i=0; i < matches; i++) {
       if (switchPlayers && i%2){ P2starts=1;}
       else{ P2starts=0;}
//       randomizeNN(p2Brain,1.0); 
//       int result=match(boardSize,P2starts,p1Brain,randomPlayer(boardState, boardSize, player));
//       result=match(boardSize,P2starts,p1Brain,p2Brain);
       result=matchRand(boardSize,P2starts,p1Brain);

       if (result==1) p1won++;
       if (result==2) p2won++;
       if (result==3) draws++;

      }

       if(winning < p1won){ winning = p1won; cpyNN(winnerBrain, p1Brain);}

       p1won = 0;
       p2won = 0;
       draws = 0;

    for(int i=0; i < matches; i++) {
       if (switchPlayers && i%2){ P2starts=1;}
       else{ P2starts=0;}
//       randomizeNN(p2Brain,1.0); 
//       result=match(boardSize,P2starts,winnerBrain,p2Brain);
       result=matchRand(boardSize,P2starts,winnerBrain);

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

         printf("winning diff is :%d\n",winning);

  }
  
//    result=matchHuman(boardSize,P2starts,winnerBrain);
    result=matchHuman(boardSize,P2starts,p1Brain);
    freeNN(p1Brain);
    freeNN(p2Brain);
    freeNN(winnerBrain);

  return 0;
}
