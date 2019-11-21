#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "defining.h" 							   //헤더파일 포함 



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


//some utility functions//
//get an integer input from standard input (keyboard)
//return : input integer value
//         (-1 is returned if keyboard input was not integer)
int getIntegerInput(void) 
{   int input, num;
    
    num = scanf("%d", &input);
    fflush(stdin);
    if (num != 1) //if it fails to get integer
        input = -1;
    
    return input;
}

int setdollar()
{
	int i;
	
	for(i=0;i<n_user;i++)
	{
		dollar[i] = N_DOLLAR;
	}
	
	return 0;
}

//betting
int betDollar(void) 
{	int i;
	
	do
	{	printf("   -> your betting (total:$%d) :", dollar[0]);
		scanf("%d", &bet[0]);
	
		if(bet[0]>50)
			printf("   -> you only have $50! bet again\n");	
	}while (bet[0]>50||bet[0]<0);
	
	for(i=1; i<n_user; i++)
		{	bet[i] = rand()%N_MAX_BET+1;
			printf("   -> player%d bets $%d (out of $%d)\n", i, bet[i],dollar[i]);
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
	
	printf(" --> card is mixed and put into the tray.\n");
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
	
	printf(" --- server     : X ");
	printCard(cardhold[n_user][1]);
	printf("\n");
	
	printf("  -> you        : ");
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
		cardSum[user] = cardSum[user] + getCardNum(cardhold[user][i]);
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

//get action-------------------------------------------------------
int getAction_User() //user
{	int Choose_Action;
	int pulledCard;
	int continueNum = 1;
	
	do{
		Choose_Action = getIntegerInput();
		calcStepResult(0,cardCount[0]);
	
		if(Choose_Action==0)
		{	//다시카드한장을 뽑도록한다  
			cardCount[0]++;
			pulledCard = pullCard();
			cardhold[0][cardCount[0]] = pulledCard;
			
			//**************************************************************체크용**************************** 
			printf("%d\n", cardhold[0][cardCount[0]]);
			printCard(cardhold[0][cardCount[0]]);
			//카드뽑기랑 프린트카드는 문제없음  
			//********************************************************************************************
			calcStepResult(0,cardCount[0]);
			
			break;
		}
		else
		{	//카드뽑기를 그만둔다 
			continueNum = 0;
			break;
		}
	}while(cardSum[0]<22&&continueNum==1);
	
	if(cardSum[0]>21)
	{
		printf("DEAD..(sum: %d)\n", cardSum[0]);
	}
	
	return 0;
}

int getAction_Auto(int player) //players
{	int pulledCard;
	int cardcnt = 2;
	int continueNum = 1;
	
	do{
		calcStepResult(0,cardCount[0]);
		
		if(cardSum[player]<17)
		{	//다시카드한장을 뽑도록한다
			printf(" GO!\n");
			
			cardCount[player]++;
			pulledCard = pullCard();
			cardhold[player][cardCount[player]] = pulledCard;
			calcStepResult(player, cardCount[player]);
		}
		else
		{	//카드뽑기를 그만둔다 
			printf(" STAY!\n");
			
			continueNum = 0;
			break;
		}
	}while(cardSum[player]<=21&&continueNum==1);
	
	printf("DEAD..(sum: %d)\n", cardSum[player]);
	
	return 0;
}

//checking functions----------------------------------------------
//user의 결과 출력 
int checkResult_User()
{
	int i;
	
	if(cardSum[0]<21)
	{
		if(cardSum[n_user])
		{
			if(cardSum[n_user]>cardSum[0])
			{
				dollar[0] = dollar[0] - bet[0];
				
				printf("   -> your result : lose (sum:%d) --> $%d\n", cardSum[0], dollar[0]);	
			}
			else
			{
				dollar[0] = dollar[0] + bet[0];
			
				printf("   -> your result : win (sum:%d) --> $%d\n", cardSum[0], dollar[0]);	
			}
		}
		else if(cardSum[n_user]==21)
		{
			dollar[i] = dollar[i] - bet[i];
			
			printf("   -> your result : lose... Dealer was BlackJack! ($%d)\n", cardSum[0], dollar[0]);
		}
		else
		{
			dollar[0] = dollar[0] + bet[0];
			
			printf("   -> your result : win (sum:%d) --> $%d\n", cardSum[0], dollar[0]);	
		}
	}
	else if(cardSum[0]==21)
	{
		dollar[0] = dollar[0] + 2*bet[0];
		
		printf("   -> your result : win (Blackjack!) --> $%d\n", dollar[0]);	
	}
	else
	{
		dollar[i] = dollar[i] - bet[i];
		
		printf("   -> your result : lose... due to overflow! ($%d)\n", cardSum[0], dollar[0]);
	}
	
	checkDollar();
}

//player들의 결과 출력  
int checkResult_Auto(int player)
{
	if(cardSum[player]<21)
	{
		if(cardSum[n_user])
		{
			if(cardSum[n_user]>cardSum[player])
			{ 
				dollar[player] = dollar[player] - bet[player];
				
				printf("   -> player %d's result : lose (sum:%d) --> $%d\n", player, cardSum[player], dollar[player]);	
			}
			else
			{
				dollar[player] = dollar[player] + bet[player];
			
				printf("   -> player %d's result : win (sum:%d) --> $%d\n", player, cardSum[player], dollar[player]);	
			}
		}
		else if(cardSum[n_user]==21)
		{
			dollar[player] = dollar[player] - bet[player];
			
			printf("   -> player %d's result : lose... Dealer was BlackJack! ($%d)\n", player, cardSum[player], dollar[player]);
		}
		else
		{
			dollar[player] = dollar[player] + bet[player];
			
			printf("   -> player %d's result : win (sum:%d) --> $%d\n", player, cardSum[player], dollar[player]);	
		}
	}
	else if(cardSum[player]==21)
	{
		dollar[player] = dollar[player] + 2*bet[player];
		
		printf("   -> player %d's result : win (Blackjack!) --> $%d\n", player, dollar[player]);	
	}
	else
	{
		dollar[player] = dollar[player] - bet[player];
		
		printf("   -> player %d's result : lose... due to overflow! ($%d)\n", player, cardSum[player], dollar[player]);
	}
	
	checkDollar();
}

//최종결과(승리자) 출력 
int checkWinner()
{	
	int winnerSum;
	int cardSumMax = cardSum[0];
	int i;
	
	printf("Game end.\nYour money is %d", cardSum[0]);
	for(i=1;i<n_user;i++)
	{	
		printf("player %d's money is %d", i, cardSum[i]); 
	}
	//최종 자본이 최대인 사람 찾기  
 	for (i = 0; i < n_user; i++) 
	{
        if (cardSum[i] > cardSumMax) 
		{
            cardSumMax = cardSum[i];
        }
    }
	winnerSum = cardSumMax; //최대 자본값을 winnerSum에 배정  
	//최종승자 결정  
	if(winnerSum==cardSum[0])
	{	
		printf("You win!");
	}
	else if (winnerSum==cardSum[1])
	{	
		printf("player 1 is winner.");
	}	
	else if (winnerSum==cardSum[2])
	{	
		printf("player 2 is winner.");
	}
	else if (winnerSum==cardSum[3])
	{	
		printf("player 3 is winner.");
	}
	else
	{	
		printf("player 4 is winner.");
	}
	
	return 0; 
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
	setdollar();
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
		//각 플레이어가 갖고 있는 카드개수 카운트(offer card만 진행되었으므로 2장씩) 배정  
		for(i=0;i<n_user+1;i++)
		{
			cardCount[i] = 2;
		}
		printf(" ---------------------------------------------------------\n"); 
		printf("\n-------------------- GAME start ------------------------\n");
		
		do //do until the player dies or player says stop
		{
			int userAction = 0;
			
			do //do until the player dies or player says stop
			{
				printf(">>> my turn! ---------------------\n"); //사용자 턴  
				//print current card status 
				printUserCardStatus(0,cardCount[0]);
				printf("::: Action? (0 - go, others - stay) : ");
				//GO? STOP? ::: getAction()
				getAction_User(cardSum[0]);
				//check the card status :::
				calcStepResult(0,cardCount[0]);
				//check if the turn ends or not
			}while (cardSum[0]>0&&cardSum[0]<22);
			
			
			for (i=1;i<n_user;i++) //each player's turn
			{	
				printf(">>> player %d turn! -------------\n", i);
				
				getAction_Auto(i);
				
				do
				{
					int tempCalcResult;
					//print current card status
					printUserCardStatus(i,cardCount[i]);
					//GO? STOP? ::: by getAction()
					getAction_Auto(cardSum[i]);
					//check the card status :::
					//check if the turn ends or not
				}while (cardSum[i]>0&&cardSum[i]<22); //do until the player dies or player says stop
			}
		}while (cardSum[0]>0&&cardSum[0]<22);
		
			printf(">>> server turn! ------------------\n");
			do //do until the player dies or player says stop
			{
				//print current card status 
				printUserCardStatus(n_user, cardCount[n_user]);
				//GO? STOP? ::: 
				getAction_Auto(n_user);
				//check the card status ::: 
				calcStepResult(n_user,cardCount[n_user]);
				//check if the turn ends or not
			}while ((cardSum[n_user]>0&&cardSum[n_user]<22)); 
			printf("[[[[[[[ server result is ....  %d ]]]]]]]\n", cardSum[n_user]);
		//result
		printf("-------------------- ROUND %d result ....\n", roundIndex);
		//check result
		checkResult_User();
		for(i=1;i<n_user;i++)
		{
			checkResult_Auto(i);
		}
		//게임 진행할지 말지 결정  
		checkGameEnd();
		
	} while (gameEnd == 0);
	
	checkWinner();
	
	return 0;
}
