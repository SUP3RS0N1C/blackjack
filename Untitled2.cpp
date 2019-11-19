#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define N_CARDSET			1     //카드셋 개수  
#define N_CARD				52    //카드 숫자  
#define N_DOLLAR			50    //플레이어 초기자본  


#define N_MAX_CARDNUM		13    //각 벌의 한계숫자  
#define N_MAX_USER			5     //플레이어 수 상한선 
#define N_MAX_CARDHOLD		10    //플레이어가 가질 수 있는 카드 개수의 상한선 
#define N_MAX_GO			17    //
#define N_MAX_BET			5     //

#define N_MIN_ENDCARD		30    //


//card tray object
int CardTray[N_CARDSET*N_CARD];
int cardIndex = 0;							


//player info
int dollar[N_MAX_USER];						//dollars that each player has
int n_user;									//number of users


//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
int cardSum[N_MAX_USER];					//sum of the cards
int bet[N_MAX_USER];						//current betting 
int gameEnd = 0; 							//game end flag

#define n_user  3
#define MAX_MIXING_COUNT  50





int betDollar(void) 
{
	int i;
	
	do
	{
		printf("   -> your betting (total:$50) :");
		scanf("%d", &dollar[0]);
	
		if(dollar[0]>50)
			printf("   -> you only have $50! bet again\n");	
		
	}while (dollar[0]>50||dollar[0]<0);
	
	for(i=1; i<n_user; i++)
		{
			dollar[i] = rand()%10+1;
			printf("   -> player%d bets $%d (out of $50)\n", i, dollar[i]);
		}

}

int data()
{	
	int Card[52];
	int i;
	int tempVariable;
	int x, y;
	
	srand((unsigned int)time(NULL));
	for (i=0; i<52; i++)
	{	Card[i] = i + 1;
	}
	for (i=0; i<MAX_MIXING_COUNT; i++)
	{	x = rand()%52;
		y = rand()%52;
		
		if(x != y)
		{	tempVariable = Card[x];
			Card[x] = Card[y];
			Card[y] = tempVariable;
		}
	}
	for (i=0;i<52; i++)
	{	printf("%d번째: %d\n",i+1,Card[i]);
	}
	return 0; 
}

int main()
{
	betDollar();
	data();
	
	return 0;
}
