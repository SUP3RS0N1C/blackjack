int getAction_User(int cardSum) 
{	int Choose_Action;
	int pulledCard;
	
	
	do{
		printUserCardStatus(0, cardcnt/*cardcnt�� �޵��� ��*/)
		printf("::: Action? (0 - go, others - stay)");
		Choose_Action = getIntegerInput();
	
		if(Choose_Action==0)
		{	//�ٽ�ī�������� �̵����Ѵ�  
			pulledCard = pullCard();
			printCard(pulledCard);
			cardSum = cardSum + getCardNum(pulledCard);
			
		}
		else
		{	//ī��̱⸦ �׸��д� 
			return cardSum;
		}
	}while(cardSum<=21);
	
	printf("DEAD..(sum: %d)", cardSum);
	return cardSum;
}

int getAction_Auto(int user, int cardSum) 
{	int pulledCard;
	int cardcnt = 2;
	
	do{
		printUserCardStatus(user/*user �ѹ��� �޾ƾ� ��*/, cardcnt/*cardcnt�� �޵��� ��*/);
	
		if(cardSum<17)
		{	//�ٽ�ī�������� �̵����Ѵ�
			printf(" GO!");
			
			pulledCard = pullCard();
			printCard(pulledCard);
			cardSum = cardSum + getCardNum(pulledCard);
			cardcnt++;
		}
		else
		{	//ī��̱⸦ �׸��д� 
			printf(" STAY!");
			return cardSum;
		}
	}while(cardSum<=21);
	
	printf("DEAD..(sum: %d)", cardSum);
	return cardSum;
}
