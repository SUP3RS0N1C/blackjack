//�������(�¸���) ��� 
int checkWinner()
{	
	int winnerSum;
	int cardSumMax = cardSum[0];
	
	printf("Game end.\nYour money is %d", cardSum[0]);
	for(i=1;i<n_user;i++)
	{	
		printf("player %d's money is %d", i, cardSum[i]); 
	}
	//���� �ں��� �ִ��� ��� ã��  
 	for (i = 0; i < n_user; i++) 
	{
        if (cardSum[i] > cardSumMax) 
		{
            cardSumMax = arr[i];
        }
    }
	winnerSum = cardSumMax; //�ִ� �ں����� winnerSum�� ����  
	//�������� ����  
	if(winnerSum==cardSum[0])
	{	
		printf("You win!");
	}
	else if (winnerSum==cardSum[1])
	{	
		printf("player 1 is winner.",);
	}	
	else if (winnerSum==cardSum[2])
	{	
		printf("player 2 is winner.",);
	}
	else if (winnerSum==cardSum[3])
	{	
		printf("player 3 is winner.",);
	}
	else
	{	
		printf("player 4 is winner.",);
	}
}
