#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_CARDSET			1     //카드셋 개수  
#define N_CARD				52    //카드 숫자  
#define N_DOLLAR			50    //플레이어 초기자본  


#define N_MAX_CARDNUM		13    //각 벌의 한계숫자  
#define N_MAX_USER			5     //플레이어 수 상한선 
#define N_MAX_CARDHOLD		10    //플레이어가 가질 수 있는 카드 개수의 상한선 
#define N_MAX_GO			17    //최대로 진행할수있는 수  
#define N_MAX_BET			5     //플레이어의 랜덤 배팅값의 최댓값  
#define N_MIN_ENDCARD		30    //트레이에 카드가 30개 이하로 남을시 게임이 종료됨?  


//card tray object
int CardTray[N_CARDSET*N_CARD];
int cardIndex = 0;							


//player info
int dollar[N_MAX_USER];						//dollars that each player has
int n_user;									//number of users


//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
int cardSum[N_MAX_USER];			 		//sum of the cards
int bet[N_MAX_USER];						//current betting 
int gameEnd = 0; 							//game end flag

//some utility functions

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

//card processing functions ---------------

//calculate the actual card number in the blackjack game 
int getCardNum(int cardnum) 
{	 cardNum = (Card[*i] - 1) % 13;
	 switch(cardNum)
	{	case 0 :
		   num_forSum = 11;
		   *Aa = 1;
		   break;
		case 10:
		   num_forSum = 10;
		   break;
		case 11:
		   num_forSum = 10;
		   break;
		case 12:
		   num_forSum = 10;
		   break;
		default: //2~9까지는 수 자체를 더하면 됨
		   num_forSum = cardNum+1;
		   break; 
	}
}

//print the card information (e.g. DiaA)
void printCard(int cardnum) 
{	int cardShape;
	int num_forSum;
	
	cardShape = (Card[*i] - 1) / 13; //카드모양 구분
	switch(cardShape)
	{	case 0 :
		   printf("CLV ");
		   break;
		case 1 :
		   printf("HRT ");
		   break;
		case 2 :
		   printf("DIA ");
		   break;
		case 3 :
		   printf("SPD ");
		   break;
	 }
	
	cardNum = (Card[*i] - 1) % 13;  //카드숫자 구분
	 switch(cardNum)
	{	case 0 :
		   printf("A \t");
		   num_forSum = 11;
		   *Aa = 1;
		   break;
		case 10:
		   printf("J \t");
		   num_forSum = 10;
		   break;
		case 11:
		   printf("Q \t");
		   num_forSum = 10;
		   break;
		case 12:
		   printf("K \t");
		   num_forSum = 10;
		   break;
		default: //2~9까지는 수 자체를 더하면 됨
		   printf("%d \t",cardNum + 1);
		   num_forSum = cardNum+1;
		   break;
	 }
	 *i  = *i + 1;
}

//card array controllers -------------------------------

//mix the card sets and put in the array
//카드에 랜덤으로 52까지의 숫자 배정 
int mixCardTray(void) 
{	int Card[52];
	int i;
	int tempVariable;
	int x, y;
	
	srand((unsigned int)time(NULL));
	
	for (i=0; i<52; i++)
	{	Card[i] = i + 1;
	}
	
	for (i=0; i<50; i++)
	{	x = rand()%52;
		y = rand()%52;
		
		if(x != y)
		{	tempVariable = Card[x];
			Card[x] = Card[y];
			Card[y] = tempVariable;
		}
	}
	
	printf(" --> card is mixed and put into the tray.");
}

//get one card from the tray
int pullCard(void) 
{	
}

//playing game functions -----------------------------

//player settiing
int configUser(void) 
{	printf("Input the number of players (MAX:5):");
	scanf("%d", &n_user);
}

//betting
int betDollar(void) 
{	int i;
	
	do
	{	printf("   -> your betting (total:$50) :");
		scanf("%d", &bet[0]);
	
		if(bet[0]>50)
			printf("   -> you only have $50! bet again\n");	
	}while (bet[0]>50||bet[0]<0);
	
	for(i=1; i<n_user; i++)
		{	bet[i] = rand()%N_MAX_BET+1;
			printf("   -> player%d bets $%d (out of $50)\n", i, bet[i]);
		}
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
	
	printf(" --- server      : X ",);
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

int getAction(void) 
{	int Choose_Action;

	Choose_Action = getIntegerInput();
	if(Choose_Action==0)
	{	//다시카드한장을 뽑도록한다  
	}
	else
	{	//카드뽑기를 그만둔다  
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
int calcStepResult() 
{	if(getCardNum<21)
	{
		//더할수도있고 멈출수도있음  getAction()으로 받기? 
	}
	else if(getCardNum=21)
	{	printf("::: Black Jack! Congratulation, you win!!");
		//blackjack으로 플레이어 승리. 
	}
	else
	{	printf("::: Too Bad. You're DEAD");
		//lose.
	}
}

int checkResult() 
{
	
}

int checkWinner() 
{
	
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
		//each player's turn
		
		printf(">>> my turn! ---------------------");
		while ((getCardNum>0&&getCardNum<22)||getAction!=0) //do until the player dies or player says stop
			{
				//print current card status printUserCardStatus();
				//check the card status ::: calcStepResult()
				//GO? STOP? ::: getAction()
				//check if the turn ends or not
			}
		
		for (i=1;i<n_user;i++) //each player
		{	printf(">>> player %d turn! -------------", i);
			while ((getCardNum>0&&getCardNum<22)||getAction!=0) //do until the player dies or player says stop
			{
				//print current card status printUserCardStatus();
				//check the card status ::: calcStepResult()
				//GO? STOP? ::: getAction()
				//check if the turn ends or not
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
		printf("-------------------- ROUND 1 result ....");
		checkResult();
		
	} while (gameEnd == 0);
	
	checkWinner();
	
	return 0;
}
