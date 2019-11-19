int getAction_User(int cardSum) 
{	int Choose_Action;
	int pulledCard;
	
	
	do{
		printUserCardStatus(0, cardcnt/*cardcnt를 받도록 함*/)
		printf("::: Action? (0 - go, others - stay)");
		Choose_Action = getIntegerInput();
	
		if(Choose_Action==0)
		{	//다시카드한장을 뽑도록한다  
			pulledCard = pullCard();
			printCard(pulledCard);
			cardSum = cardSum + getCardNum(pulledCard);
			
		}
		else
		{	//카드뽑기를 그만둔다 
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
		printUserCardStatus(user/*user 넘버를 받아야 함*/, cardcnt/*cardcnt를 받도록 함*/);
	
		if(cardSum<17)
		{	//다시카드한장을 뽑도록한다
			printf(" GO!");
			
			pulledCard = pullCard();
			printCard(pulledCard);
			cardSum = cardSum + getCardNum(pulledCard);
			cardcnt++;
		}
		else
		{	//카드뽑기를 그만둔다 
			printf(" STAY!");
			return cardSum;
		}
	}while(cardSum<=21);
	
	printf("DEAD..(sum: %d)", cardSum);
	return cardSum;
}
