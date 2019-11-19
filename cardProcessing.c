//card processing functions ---------------

//calculate the actual card number in the blackjack game 
int getCardNum(int card) 
{	
	int num_forSum;
	
	 switch((cardNum - 1) % 13)
	{	case 1 ://A�� ���� ��� 
		   num_forSum = 11;
		   //23�� ���� ��� 1�� ���ǵ��� �Լ� �ۿ��� ����  
		   break;
		case 2 ://J�� ���� ��� 
		   num_forSum = 10;
		   break;
		case 3 ://Q�� ���� ��� 
		   num_forSum = 10;
		   break;
		case 4 ://K�� ���� ��� 
		   num_forSum = 10;
		   break;
		default: //2~9������ �� ��ü�� ���Ѵ�  
		   num_forSum = cardNum+1;
		   break; 
	}
	
	return num_forSum;
}

//print the card information (e.g. DiaA)
void printCard(int card) 
{	
	int num_forSum;
	
	//ī���� ����
	switch((CardNum -1) / 13)
	{	case 0 :
		   printf("CLV ");
		   break;
		case 1 :
		   printf("HRT ");
		   break;
		case 2 :
		   printf("DIA ");
		   break;
		case 3 :
		   printf("SPD ");
		   break;
	 }
	
	//ī����� ���� 
	 switch((cardNum -1) % 13)
	{	case 0 ://A�� ���� ���  
		   printf("A \t");
		   break;
		case 10 ://J�� ���� ���  
		   printf("J \t");
		   break;
		case 11 ://Q�� ���� ���  
		   printf("Q \t");
		   break;
		case 12 ://K�� ���� ���  
		   printf("K \t");
		   break;
		default : //2~9������ �� ��ü�� ���ϵ��� ��  
		   printf("%d \t",cardNum + 1);
		   break;
	 }
}

