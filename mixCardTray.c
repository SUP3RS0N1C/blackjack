//mix the card sets and put in the array
//ī�忡 �������� N_CARD(52)������ ���� ���� 
int mixCardTray(void) 
{
	int i;
	int tempVariable;
	int x, y; //�迭�� ���� ���� 
	
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

