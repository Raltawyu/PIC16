


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"




#define InstrColor 	"\033[0;94m"
#define OPColor 		"\033[0;95m"
#define TxtReset		"\033[0;0m"  
#define BlueTxt		"\033[0;33m"
#define MagentaTxt	"\033[0;96m"	
#define GreenTxt		"\033[0;92m"
#define RedTxt			"\033[0;91m"



/*   ----- Calculus power of base 2 -----   */


int pot2(int pot){

	int res = 0;
		
	if(pot == 0)
	{
		res = 1;
		return res;
	}
	else
	{
		res = 2;
		for(int i=1; i<pot; i++)  
			res = res * 2;
		return res;		
	}
	
}



		/*  ----- Converto Integer to Binary  ----- */


char *INTtoBIN(int value, int lenght)
{ 
		char *bin_string = (char*)malloc((lenght+1)*sizeof(char)); 
		if(bin_string == NULL)
		{	
			printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
			exit(1);
		}	
			
		int i = lenght, j=0;
		
		while(j<=lenght)
		{	
			if( (value-pot2(i)) >= 0 )
			{
				value = value - pot2(i);	
				bin_string[j] = '1';
			}
			else{
				bin_string[j] = '0';
			}
			
			j++;
			i--; 
		} 
		
		bin_string[lenght+1] = '\0';
		 
	 	return &bin_string[1];
}



		/*  ----- Converto Hexadecimal to Binary  ----- */

char *HEXtoBIN(char *Hex_String)
{
	int Hex_Lenght = strlen(Hex_String);
	int Bin_Lenght = 1 + (Hex_Lenght*4);
	
	char *Bin_String = (char *)malloc(Bin_Lenght*sizeof(char));
	if(Bin_String == NULL)
	{
		printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
		exit(1);
	}
	
	if(Hex_String != NULL)
	{
		for(int j=0, i=0; j<=Hex_Lenght; j++, i+=4)
		{
			if( Hex_String[j] == '0' )
			{
				Bin_String[i] = '0';
				Bin_String[i+1] = '0';
				Bin_String[i+2] = '0';
				Bin_String[i+3] = '0'; 
			}
			else if(Hex_String[j] == '1')
			{
				Bin_String[i] = '0';
				Bin_String[i+1] = '0';
				Bin_String[i+2] = '0';
				Bin_String[i+3] = '1'; 
			}
			else if(Hex_String[j] == '2')
			{
				Bin_String[i] = '0';
				Bin_String[i+1] = '0';
				Bin_String[i+2] = '1';
				Bin_String[i+3] = '0'; 
			}
			else if(Hex_String[j] == '3')
			{
				Bin_String[i] = '0';
				Bin_String[i+1] = '0';
				Bin_String[i+2] = '1';
				Bin_String[i+3] = '1'; 
			}
			else if(Hex_String[j] == '4')
			{
				Bin_String[i] = '0';
				Bin_String[i+1] = '1';
				Bin_String[i+2] = '0';
				Bin_String[i+3] = '0'; 
			}
			else if(Hex_String[j] == '5')
			{
				Bin_String[i] = '0';
				Bin_String[i+1] = '1';
				Bin_String[i+2] = '0';
				Bin_String[i+3] = '1'; 
			}
			else if(Hex_String[j] == '6')
			{
				Bin_String[i] = '0';
				Bin_String[i+1] = '1';
				Bin_String[i+2] = '1';
				Bin_String[i+3] = '0'; 
			}
			else if(Hex_String[j] == '7')
			{
				Bin_String[i] = '0';
				Bin_String[i+1] = '1';
				Bin_String[i+2] = '1';
				Bin_String[i+3] = '1'; 
			}
			else if(Hex_String[j] == '8')
			{
				Bin_String[i] = '1';
				Bin_String[i+1] = '0';
				Bin_String[i+2] = '0';
				Bin_String[i+3] = '0'; 
			}
			else if(Hex_String[j] == '9')
			{
				Bin_String[i] = '1';
				Bin_String[i+1] = '0';
				Bin_String[i+2] = '0';
				Bin_String[i+3] = '1'; 
			}
			else if(Hex_String[j] == 'A')
			{
				Bin_String[i] = '1';
				Bin_String[i+1] = '0';
				Bin_String[i+2] = '1';
				Bin_String[i+3] = '0'; 
			}
			else if(Hex_String[j] == 'B')
			{
				Bin_String[i] = '1';
				Bin_String[i+1] = '0';
				Bin_String[i+2] = '1';
				Bin_String[i+3] = '1'; 
			}
			else if(Hex_String[j] == 'C')
			{
				Bin_String[i] = '1';
				Bin_String[i+1] = '1';
				Bin_String[i+2] = '0';
				Bin_String[i+3] = '0'; 
			}else if(Hex_String[j] == 'D')
			{
				Bin_String[i] = '1';
				Bin_String[i+1] = '1';
				Bin_String[i+2] = '0';
				Bin_String[i+3] = '1'; 
			}
			else if(Hex_String[j] == 'E')
			{
				Bin_String[i] = '1';
				Bin_String[i+1] = '1';
				Bin_String[i+2] = '1';
				Bin_String[i+3] = '0'; 
			}
			else if(Hex_String[j] == 'F')
			{
				Bin_String[i] = '1';
				Bin_String[i+1] = '1';
				Bin_String[i+2] = '1';
				Bin_String[i+3] = '1'; 
			}
		}
	
	}
	
	Bin_String[Bin_Lenght-1] = '\0';

	return Bin_String;
}












