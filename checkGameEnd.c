#include "defining.h" 

extern int n_user;
extern int gameEnd;
extern int cardIndex;
extern int dollar[N_MAX_USER];


//게임 종료 여부 판단
int checkGameEnd()
{
	gameEnd = checkCardTray();
	gameEnd = checkDollar();
	
} 

//카드트레이에 남은 카드의 갯수를 확인, 카드가 소진될 시 게임 종료 
int checkCardTray()
{
	if(cardIndex>N_CARDSET*N_CARD - n_user*2)
	{
		printf("Card ran out of the tray!! Finishing the game...");
		
		gameEnd = 1;
		
		return 1;
	}
	
	if(cardIndex==N_CARDSET*N_CARD)
	{
		printf("Card ran out of the tray!! Finishing the game...");
		
		gameEnd = 1;
		
		return 1;
	}
	else
	{
		gameEnd =0;
		
		return 0;
	}
}

//남은 배팅액을 확인, 자본을 모두 소진하였을 경우 게임 종료
int checkDollar()
{
	int i;
	
	for(i=0;i<n_user;i++)
	{
		if(dollar[i]<1)
		{
			printf("One of the players is bankrupted. Finishing the game...");
			
			gameEnd =1;
			
			return 1; 
		}
		else
		{
			gameEnd =0;
			
			return 0;
		}
	}
} 
