int betDollar(void) 
{
	do
	{
		printf("   -> your betting (total:$50) :");
		scanf("%d", &dollar[0]);
	
		if(dollar[0]>50)
			printf("   -> you only have $50! bet again\n");	
		
	}while (dollar[0]>50||dollar[0]<0);
	
	for(i=1; i<n_user-1; i++)
		{
			dollar[i] = rand()%50+1;
			printf("   -> player%d bets $%d (out of $50)\n", i, dollar[i]);
		}

}
int main()
{
	betDollar();
	
	return 0;
}
