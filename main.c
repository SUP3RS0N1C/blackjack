#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "defining.h"    //헤더파일 포함 

//card tray object
int CardTray[N_CARDSET*N_CARD] = {0,};
int cardIndex = 0;							


//player info
int dollar[N_MAX_USER] = {50,};						//dollars that each player has
int n_user;											//number of users


//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD] = {0,};	//cards that currently the players hold
int cardSum[N_MAX_USER] = {0,};				 		//sum of the cards
int bet[N_MAX_USER];								//current betting 
int gameEnd = 0; 									//game end flag



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
{	int i;	
	//1. give two card for each players
	for (i=0;i<n_user;i++)
	{	cardhold[i][0] = pullCard();
		cardhold[i][1] = pullCard();
	}
	//2. give two card for the operator
	cardhold[n_user][0] = pullCard();
	cardhold[n_user][1] = pullCard();
	
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
int calcStepResult(int cardSum) 
{	
	if(cardSum<21)
		{	
			
		}
		else if(cardSum==21)
		{	//blackjack으로 플레이어 승리. 
			printf("::: Black Jack! Congratulation, you win!!");
		}
		else
		{
			printf("[[[[[[[ result is .... ....overflow!! ]]]]]]]");
		}
	
	
}

int checkResult()
{
	if(cardSum[0]<cardSum[n_user])
		printf("   -> your result : lose (sum:%d) --> $%d", cardSum[0], dollar[0]);
	else
		printf("   -> your result : win (sum:%d) --> $%d", cardSum[0], dollar[0]);
	
}

//카드트레이에 남은 카드의 갯수를 확인, 카드가 소진될 시 게임 종료 
int checkCardTray()
{
	if(cardIndex==N_CARDSET*N_CARD-1)
	{
		printf("card ran out of the tray!! finishing the game...");
		
		return 1;
	}
	else
	{
		return 0;
	}
}

int main(int argc, char *argv[]) 
{	int roundIndex = 0;
	int max_user;
	int i;
	
	srand((unsigned)time(NULL));
	
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
		printf(" ---------------------------------------------------------\n\n"); 
		
		printf("\n-------------------- GAME start ------------------------\n");
		
		while ((cardSum>0&&cardSum<22)) //do until the player dies or player says stop
			{
				int userAction = 0;
				
				printf(">>> my turn! ---------------------"); //사용자 턴  
				printUserCardStatus(0,cardcnt);
				userAction = getAction_User();
				
				if(userAction == 0)
				{	
				}
				else
				{	
				}
				//print current card status printUserCardStatus();
				//check the card status ::: calcStepResult()
				//GO? STOP? ::: getAction()
				//check if the turn ends or not
				
				for (i=1;i<n_user;i++) //each player's turn
				{	
					printf(">>> player %d turn! -------------", i);
					
					getAction_Auto(i,)
					while ((getCardNum>0&&getCardNum<22)) //do until the player dies or player says stop
					{
						int tempCalcResult;
						//print current card status 
						printUserCardStatus();
						//check the card status ::: 
						tempCalcResult = calcStepResult();
						getAction_Auto(tempCalcResult);
						//GO? STOP? ::: getAction()
						//check if the turn ends or not
					}
				}
			}
		
			printf(">>> server turn! ------------------");
			while ((getCardNum>0&&getCardNum<22)||getAction!=0) //do until the player dies or player says stop
			{
				//print current card status printUserCardStatus();
				//check the card status ::: calcStepResult()
				//GO? STOP? ::: getAction()
				//check if the turn ends or not
			}
		//result
		printf("-------------------- ROUND %d result ....", roundIndex);
		checkResult();
		
	} while (gameEnd == 0);
	
	checkWinner();
	
	return 0;
}
