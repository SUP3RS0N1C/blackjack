//���� ���� ���� �Ǵ�
int checkGameEnd()
{
	gameEnd = checkCardTray();
	gameEnd = checkDollar();
	
} 

//ī��Ʈ���̿� ���� ī���� ������ Ȯ��, ī�尡 ������ �� ���� ���� 
int checkCardTray()
{
	if(cardIndex==N_CARDSET*N_CARD)
	{
		printf("card ran out of the tray!! finishing the game...");
		
		gameEnd =1;
		
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
	if(dollar[i]<1)
	{
		printf("You're PASANed...");
		
		gameEnd =1;
		
		return 1; 
	}
	else
	{
		gameEnd =0;
		
		return 0;
	}
} 
