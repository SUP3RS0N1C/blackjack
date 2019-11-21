#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "defining.h"    //헤더파일 포함 k

//card tray object
int CardTray[N_CARDSET*N_CARD] = {0,};
int cardIndex = 0;							


//player info
int dollar[N_MAX_USER];								//dollars that each player has
int n_user;											//number of users


//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD] = {0,};	//cards that currently the players hold
int cardSum[N_MAX_USER] = {0,};				 		//sum of the cards
int bet[N_MAX_USER];								//current betting 
int gameEnd = 0; 									//game end flag

int cardCount[N_MAX_USER];


void put_capital()
{
	int i;
	
	for(i=0;i<N_MAX_USER;i++)
	{
		dollar[i] = N_DOLLAR;
	}
}

//card array controllers -------------------------------

//mix the card sets and put in the array
//카드에 랜덤으로 N_CARD(52)까지의 숫자 배정 
int mixCardTray(void) 
{
	int i;
	int tempVariable;
	int x, y; //배열상의 임의 숫자 
	
	srand((unsigned int)time(NULL));
	
	for (i=0; i<N_CARD*N_CARDSET; i++)
	{	CardTray[i] = i + 1;
	}
	
	for (i=0; i<50; i++)
	{	x = rand()%N_CARD*N_CARDSET;
		y = rand()%N_CARD*N_CARDSET;
		
		if(x != y)
		{	tempVariable = CardTray[x];
			CardTray[x] = CardTray[y];
			CardTray[y] = tempVariable;
		}
	}
	
	printf(" --> card is mixed and put into the tray.");
}

//get one card from the tray
int pullCard(void) 
{
	cardIndex ++;
	checkCardTray();
	
	return CardTray[cardIndex-1];
}

//playing game functions -----------------------------

//player settiing
int configUser(void) 
{	printf("Input the number of players (MAX:5):");
	scanf("%d", &n_user);
}

//offering initial 2 cards
void offerCards(void) 
{	int i,j;	//for문에 사용할 변수  
	
	for(j=0;j<2;j++)
	{
		//offer card for operator
		cardhold[n_user][j] = pullCard();
	
		//offer cards for each players
		for (i=0;i<n_user;i++)
		{	
			cardhold[i][j] = pullCard();
		}
	}
	
	return;
}

//print initial card status
void printCardInitialStatus(void) 
{	int i;
	
	printf(" --- server      : X ");
	printCard(cardhold[n_user][1]);
	printf("\n");
	
	printf("  -> you         : ");
	printCard(cardhold[0][0]);
	printCard(cardhold[0][1]);
	printf("\n");
	
	for(i=1;i<n_user;i++)
	{	printf("  -> player %d   : ", i);
		printCard(cardhold[i][0]);
		printCard(cardhold[i][1]);
		printf("\n");
	}
}

void printUserCardStatus(int user, int cardcnt) 
{	int i;
	
	printf("   -> card : ");
	for (i=0;i<cardcnt;i++)
		printCard(cardhold[user][i]);
	printf("\t ::: ");
}

// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult(int user,int cardcnt)
{	
	int decide = 0;
	int i;
	cardSum[user] = 0;
	
	for(i=0;i<cardcnt;i++)
	{
		cardSum[user] = cardSum[user] + cardhold[user][i];
	}
	//A카드의 존재 여부 확인  
	for(i=0;i<cardcnt;i++)
	{
		if(cardhold[user][i]==0)
			decide = 1;
		else
			decide = decide;
	}
	//A의 값 결정 (1 or 11)
	if(decide==1&&cardSum[user]>21)//21이 넘을 경우 1로 변환  
	{
		cardSum[user] = cardSum[user] -10; 
	}
	else//21을 넘지 않은 경우 그대로 A=11 값을 사용  
	{
		cardSum[user] = cardSum[user];
	}
	
	return 0;
}

int checkResult()
{
	int i;
	
	if(cardSum[0]==21)
	{
		dollar[0] = dollar[0] + 3*bet[0];
		
		printf("   -> your result : win (Blackjack!) --> $%d", dollar[0]);	
	}
	else
	{
		if(cardSum[0]>21||cardSum[0]<cardSum[n_user])
		{
			printf("   -> your result : lose due to overflow! ($%d)", cardSum[0], dollar[0]);
		}
		else
		{
			dollar[0] = dollar[0] + 2*bet[0];
			
			printf("   -> your result : win (sum:%d) --> $%d", cardSum[0], dollar[0]);		
		}
	}
	
	for(i=0;i<n_user;i++)
	{
		if(cardSum[i]==21)
		{
			dollar[i] = dollar[i] + 3*bet[i];
			
			printf("   -> %d'th player's result : win (Blackjack!) --> $%d", dollar[i]);
		}
		else
		{
			if(cardSum[i]>21||cardSum[i]<cardSum[n_user])
			{
				printf("   -> your result : lose due to overflow! ($%d)", cardSum[i], dollar[i]);
			}
			else
			{
				dollar[i] = dollar[i] + 2*bet[i];
				
				printf("   -> your result : win (sum:%d) --> $%d", cardSum[i], dollar[i]);	
			}
		}
	}
	
	return 0;
}

int main(int argc, char *argv[]) 
{	int roundIndex = 0;
	int max_user;
	int i;
	
	srand((unsigned)time(NULL));
	
	//자본 N_DOLLAR로 배정하기
	put_capital(); 
	
	//set the number of players
	configUser();

	//Game initialization --------
	//1. players' dollar
	//2. card tray
	mixCardTray();
	
	//Game start --------
	do 
	{	roundIndex++;
		
		printf("--------------------------------------------------------------\n");
		printf("---------------- ROUND %d (cardIndex:%d)----------------------\n",roundIndex,cardIndex);
		printf("--------------------------------------------------------------\n");
	
		printf(" --------------------- BETTING STEP ----------------------\n"); 
		betDollar();
		printf(" ---------------------------------------------------------\n"); 
		
		printf(" -------------------- CARD OFFERING ----------------------\n"); 
		offerCards(); //1. give cards to all the players
		printCardInitialStatus(); //print offerd card's status
		//*******************************************니가안함********************************************************************** 
		//cardCount 2값으로 모두 초기화배정 
		//*******************************************니가안함********************************************************************** 
		printf(" ---------------------------------------------------------\n\n"); 
		
		printf("\n-------------------- GAME start ------------------------\n");
		
		while ((cardSum[0]>0&&cardSum[0]<22)) //do until the player dies or player says stop
			{
				int userAction = 0;
				
				printf(">>> my turn! ---------------------"); //사용자 턴  
				
				//print current card status 
				printUserCardStatus(0, cardCount[0]);
				printf("::: Action? (0 - go, others - stay)");
				//check the card status ::: calcStepResult()
				//GO? STOP? ::: getAction()
				//check if the turn ends or not
				
				for (i=1;i<n_user;i++) //each player's turn
				{	
					printf(">>> player %d turn! -------------", i);
					
					getAction_Auto(i,cardCount[0]);
					while ((getCardNum>0&&getCardNum<22)) //do until the player dies or player says stop
					{
						int tempCalcResult;
						//print current card status 
						printUserCardStatus();
						//check the card status ::: 
						calcStepResult();
						//GO? STOP? ::: by getAction()
						getAction_Auto(cardSum[i]);
						
						//check if the turn ends or not
					}
				}
			}
		
			printf(">>> server turn! ------------------");
			{	
				//print current card status 
				
					printUserCardStatus(user, cardCount[user]);
				//check the card status ::: calcStepResult()
				
				//GO? STOP? ::: getAction()
				//check if the turn ends or not
			}while ((cardSum[n_user]>0&&cardSum[n_user]<22)||getAction_Auto()!=0) //do until the player dies or player says stop
		//result
		printf("-------------------- ROUND %d result ....", roundIndex);
		checkResult();
		checkGameEnd();
		
	} while (gameEnd == 0);
	
	checkWinner();
	
	return 0;
}
