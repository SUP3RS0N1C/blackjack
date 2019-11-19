//mix the card sets and put in the array
//카드에 랜덤으로 N_CARD(52)까지의 숫자 배정 
int mixCardTray(void) 
{
	int i;
	int tempVariable;
	int x, y; //배열의 임의 숫자 
	
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
	
	printf(" --> card is mixed and put into the tray.");
}

