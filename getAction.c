int getAction_User(int cardSum) 
{	int Choose_Action;
	int pulledCard;
	
	do{
		Choose_Action = getIntegerInput();
	
		if(Choose_Action==0)
		{	//�ٽ�ī�������� �̵����Ѵ�  
			pullCard();
			cardSum[0] = cardSum[0] + getCardNum(pulledCard);
			cardCount[0]++;
		}
		else
		{	//ī��̱⸦ �׸��д� 
			return 0;
		}
	}while(cardSum<=21);
	
	printf("DEAD..(sum: %d)", cardSum);
	
	return 0;
}

int getAction_Auto(int user) 
{	int pulledCard;
	int cardcnt = 2;
	
	do{
		if(cardSum[user]<17)
		{	//�ٽ�ī�������� �̵����Ѵ�
			printf(" GO!");
			
			pullCard();
			cardSum[user] = cardSum[user] + getCardNum(pulledCard);
			cardCount[user]++;
		}
		else
		{	//ī��̱⸦ �׸��д� 
			printf(" STAY!");
		}
	}while(cardSum<=21);
	
	printf("DEAD..(sum: %d)", cardSum[user]);
	
	return 0;
}
