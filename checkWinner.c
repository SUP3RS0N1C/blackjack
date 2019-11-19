//최종결과(승리자) 출력 
int checkWinner()
{	
	int winnerSum;
	int cardSumMax = cardSum[0];
	
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
            cardSumMax = arr[i];
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
