#include "defining.h" 

extern int n_user;
extern int gameEnd;
extern int cardIndex;
extern int dollar[N_MAX_USER];


//���� ���� ���� �Ǵ�
int checkGameEnd()
{
	gameEnd = checkCardTray();
	gameEnd = checkDollar();
	
} 

//ī��Ʈ���̿� ���� ī���� ������ Ȯ��, ī�尡 ������ �� ���� ���� 
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

//���� ���þ��� Ȯ��, �ں��� ��� �����Ͽ��� ��� ���� ����
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
