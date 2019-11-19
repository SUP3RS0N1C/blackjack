//card processing functions ---------------

//calculate the actual card number in the blackjack game 
int getCardNum(int card) 
{	
	int num_forSum;
	
	 switch((cardNum - 1) % 13)
	{	case 1 ://A를 뽑은 경우 
		   num_forSum = 11;
		   //23이 넘을 경우 1로 계산되도록 함수 밖에서 조정  
		   break;
		case 2 ://J를 뽑은 경우 
		   num_forSum = 10;
		   break;
		case 3 ://Q를 뽑은 경우 
		   num_forSum = 10;
		   break;
		case 4 ://K를 뽑은 경우 
		   num_forSum = 10;
		   break;
		default: //2~9까지는 수 자체를 더한다  
		   num_forSum = cardNum+1;
		   break; 
	}
	
	return num_forSum;
}

//print the card information (e.g. DiaA)
void printCard(int card) 
{	
	int num_forSum;
	
	//카드모양 구분
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
	
	//카드숫자 구분 
	 switch((cardNum -1) % 13)
	{	case 0 ://A를 뽑은 경우  
		   printf("A \t");
		   break;
		case 10 ://J를 뽑은 경우  
		   printf("J \t");
		   break;
		case 11 ://Q를 뽑은 경우  
		   printf("Q \t");
		   break;
		case 12 ://K를 뽑은 경우  
		   printf("K \t");
		   break;
		default : //2~9까지는 수 자체를 더하도록 함  
		   printf("%d \t",cardNum + 1);
		   break;
	 }
}

