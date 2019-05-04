#include <stdio.h>
#include <time.h>
#include<stdio.h>
#include <math.h> 

#include"Header/match.h"
#include"Header/ann.h"


int main(int argc, char* argv[]){
    srand(time(NULL));

	short boardSize = 16;
	int matches=10;
    int d = 2;
    int h = 2;
    int popSize=10;
    int genSize=10;
	int switchPlayers=1;
    int result;
    int winning = -100000;
    int* current[1];

    int oldp1won = 100000; int oldp2won = 100000; int olddraw  = 100000;

//printf("a\n");
//    myANN* p1Brain = initANN(9, h, d, 1);
    myANN* p2Brain = initANN(16, h, d, 1);
    myANN* winnerBrain = initANN(16, h, d, 1);
    myANN* winnerBrain2 = initANN(16, h, d, 1);

    myANN** Brains = malloc(sizeof(myANN*)*popSize);
    myANN** BabyBrains = malloc(sizeof(myANN*)*popSize);

    myANN** Brains2 = malloc(sizeof(myANN*)*popSize);
    myANN** BabyBrains2 = malloc(sizeof(myANN*)*popSize);

    int* wonNum = malloc(sizeof(int)*popSize);
    int* wonNum2 = malloc(sizeof(int)*popSize);

    for(int i = 0; i < popSize; i++){
    
      Brains[i] =  initANN(16, h, d, 1);
      BabyBrains[i] =initANN(16, h, d, 1);

      Brains2[i] =  initANN(16, h, d, 1);
      BabyBrains2[i] =initANN(16, h, d, 1);
        
    }

    for(int i = 0; i < popSize; i++){
    
      randomizeNN(Brains[i], 0.0);
      randomizeNN(Brains2[i], 0.0);
        
    }

//printf("b\n");
//    randomizeNN(p2Brain,1.0);
//    randomizeNN(p1Brain,1.0);

    int player = 0;
	int draws=0,p1won=0,p2won=0;

	srand(time(NULL));

	int P2starts=1;

//       randomizeNN(p2Brain,1.0);
//       randomizeNN(p1Brain,1.0);

    for(int gens=0; gens < genSize; gens++){ 

      printf("%d gens\n",gens);

      for(int pops=0; pops < popSize; pops++){ 

       for(int i=0; i < matches; i++){
//         randomizeNN(p2Brain,1.0);
         if (switchPlayers && i%2){ P2starts=1;}
         else{ P2starts=0;}
		 result=matchRand(boardSize,P2starts,Brains[pops]);
//		 result=match(boardSize,P2starts,Brains[pops],Brains2[pops]);
//         rintf("c\n");
		 if (result==1) p1won++;
         if (result==2) p2won++;
         if (result==3) draws++;

      }

//printf("d\n");
      wonNum[pops] = p1won - p2won - (int)floor(100*weightSum(Brains[pops]));
//      wonNum2[pops] = p2won - p1won - (int)floor(0.1*weightSum(Brains[pops]));
//      printf("w:%f\n", 1000*weightSum(Brains[pops]));
        
      p1won = 0;
      p2won = 0;
      draws = 0;

    }
//      printf("w: %i\n", (int)floor(0.1*weightSum(Brains[0])));
//      printf("p: %f\n", Brains[0] -> wI[0]);
      
//printf("e\n");
    for(int i = 0; i < popSize; i++){
//printf("%d\n",softMaxDec(wonNum,popSize));
       cpyNN(BabyBrains[i], mateNN(Brains[softMaxDec(wonNum,popSize)], Brains[softMaxDec(wonNum,popSize)],gens));
//       cpyNN(BabyBrains2[i], mateNN(Brains[softMaxDec(wonNum2,popSize)], Brains[softMaxDec(wonNum2,popSize)],gens));
    }
    for(int i = 0; i < popSize; i++){
       cpyNN(Brains[i], BabyBrains[i]);
 //      cpyNN(Brains2[i], BabyBrains2[i]);
    }
//printf("f\n");

//printf("f\n");
    for(int i=0; i < matches; i++) {
       if (switchPlayers && i%2){ P2starts=1;}
       else{ P2starts=0;}
       randomizeNN(p2Brain,1.0); 
//       int result=match(boardSize,P2starts,p1Brain,randomPlayer(boardState, boardSize, player));
//       result=match(boardSize,P2starts,p1Brain,p2Brain);
//       result=match(boardSize,P2starts,Brains[getMaxIndx(wonNum,popSize)],Brains[getMaxIndx(wonNum2,popSize)]);
       result=matchRand(boardSize,P2starts,Brains[getMaxIndx(wonNum,popSize)]);

       if (result==1) p1won++;
       if (result==2) p2won++;
       if (result==3) draws++;

      }

       if(winning <  p1won - p2won ){ winning =  p1won - p2won ; cpyNN(winnerBrain,Brains[getMaxIndx(wonNum,popSize)]);}
//       if(winning <  p2won - p1won ){ winning =  p2won - p1won ; cpyNN(winnerBrain2,Brains2[getMaxIndx(wonNum2,popSize)]);}

//printf("g\n");
       p1won = 0;
       p2won = 0;
       draws = 0;

    for(int i=0; i < matches; i++) {
       if (switchPlayers && i%2){ P2starts=1;}
       else{ P2starts=0;}
       randomizeNN(p2Brain,1.0); 
       result=match(boardSize,P2starts,winnerBrain,p2Brain);
//       result=matchRand(boardSize,P2starts,winnerBrain);

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

//    winnerBrain -> bO[0] = 10;
//    winnerBrain -> bO[1] = -10;
  
    result=matchHuman(boardSize,1,winnerBrain);
//    freeNN(p1Brain);
//    freeNN(p2Brain);
    freeNN(winnerBrain);
    freeNN(winnerBrain2);

  return 0;
}
