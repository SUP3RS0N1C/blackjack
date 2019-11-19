//betting
int betDollar(void) 
{	int i;
	
	do
	{	printf("   -> your betting (total:$%d) :", dollar[0]);
		scanf("%d", &bet[0]);
	
		if(bet[0]>50)
			printf("   -> you only have $50! bet again\n");	
	}while (bet[0]>50||bet[0]<0);
	dollar[0] = dollar[0]-bet[0];
	
	for(i=1; i<n_user; i++)
		{	bet[i] = rand()%N_MAX_BET+1;
			printf("   -> player%d bets $%d (out of $%d)\n", i, bet[i],dollar[i]);
			dollar[i] = dollar[i] - bet[i];
		}
}
