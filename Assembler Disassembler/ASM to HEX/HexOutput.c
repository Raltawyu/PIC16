

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





		/*  ----- Power of 16 -----  */


int pot16(int pot)							
{
	int res = 0;
	
	if(pot == 0)
	{
		res = 1;
		return res;
	}
	else
	{
		res = 16;
		for(int i=1; i<pot; i++)  
			res = res * 16;
		return res;		
	}	
}




		/*  ----- Converting BinString to HexString function -----  */


char *BinStringToHexString(char *BinString, int n_chars)
{
	
	int n_bit = 4*n_chars;

	char *Hex_String = (char *)malloc((n_chars+1)*sizeof(char));
	if(Hex_String == NULL)
	{
		printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
		exit(1);
	}	
	
	unsigned int Lenght_BinString = strlen(BinString);								// Formatting input string in n_byte string  

	char *Formatted_Bin_String = (char *)calloc(n_bit , sizeof(char));
	if(Formatted_Bin_String == NULL)
	{
		printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
		exit(1);
	}
	
	Formatted_Bin_String[n_bit] = '\0';
	
	for(int i=n_bit-1; i>=0; i--)
	{
		if( Lenght_BinString>0 )
		{
			Formatted_Bin_String[i] = BinString[Lenght_BinString-1];
			 Lenght_BinString--;
		}	 
		else
			Formatted_Bin_String[i] = '0';
		
	}
	
	
	Hex_String[n_chars] = '\0';													 		//  Generating Output String  

	
	for(int i=n_chars-1; i>=0 ; i--, n_bit-=4)
	{
		if( Formatted_Bin_String[n_bit-4] == '1' && Formatted_Bin_String[n_bit-3] == '1' && 
			 Formatted_Bin_String[n_bit-2] == '1' && Formatted_Bin_String[n_bit-1] == '1' )
			
				Hex_String[i] = 'F';
		
		else if( Formatted_Bin_String[n_bit-4] == '1' && Formatted_Bin_String[n_bit-3] == '1' && 
					Formatted_Bin_String[n_bit-2] == '1' && Formatted_Bin_String[n_bit-1] == '0' )
		
				Hex_String[i] = 'E';
		
		else if( Formatted_Bin_String[n_bit-4] == '1' && Formatted_Bin_String[n_bit-3] == '1' && 
					Formatted_Bin_String[n_bit-2] == '0' && Formatted_Bin_String[n_bit-1] == '1' )
		{
				Hex_String[i] = 'D';
		}
		
		else if( Formatted_Bin_String[n_bit-4] == '1' && Formatted_Bin_String[n_bit-3] == '1' && 
					Formatted_Bin_String[n_bit-2] == '0' && Formatted_Bin_String[n_bit-1] == '0' )
			
				Hex_String[i] = 'C';
		
		else if( Formatted_Bin_String[n_bit-4] == '1' && Formatted_Bin_String[n_bit-3] == '0' &&
					Formatted_Bin_String[n_bit-2] == '1' && Formatted_Bin_String[n_bit-1] == '1' )
		
				Hex_String[i] = 'B';
	
		else if( Formatted_Bin_String[n_bit-4] == '1' && Formatted_Bin_String[n_bit-3] == '0' && 
					Formatted_Bin_String[n_bit-2] == '1' && Formatted_Bin_String[n_bit-1] == '0' )
		
				Hex_String[i] = 'A';
		
		else if( Formatted_Bin_String[n_bit-4] == '1' && Formatted_Bin_String[n_bit-3] == '0' && 
					Formatted_Bin_String[n_bit-2] == '0' && Formatted_Bin_String[n_bit-1] == '1' )
		
				Hex_String[i] = '9';
				
		else if( Formatted_Bin_String[n_bit-4] == '1' && Formatted_Bin_String[n_bit-3] == '0' && 
					Formatted_Bin_String[n_bit-2] == '0' && Formatted_Bin_String[n_bit-1] == '0' )
			
				Hex_String[i] = '8';
		
		else if( Formatted_Bin_String[n_bit-4] == '0' && Formatted_Bin_String[n_bit-3] == '1' && 
					Formatted_Bin_String[n_bit-2] == '1' && Formatted_Bin_String[n_bit-1] == '1' )
		
				Hex_String[i] = '7';
	
		else if( Formatted_Bin_String[n_bit-4] == '0' && Formatted_Bin_String[n_bit-3] == '1' && 
					Formatted_Bin_String[n_bit-2] == '1' && Formatted_Bin_String[n_bit-1] == '0' )
		
				Hex_String[i] = '6';
		
		else if( Formatted_Bin_String[n_bit-4] == '0' && Formatted_Bin_String[n_bit-3] == '1' && 
					Formatted_Bin_String[n_bit-2] == '0' && Formatted_Bin_String[n_bit-1] == '1' )
		
				Hex_String[i] = '5';
		
		else if( Formatted_Bin_String[n_bit-4] == '0' && Formatted_Bin_String[n_bit-3] == '1' && 
					Formatted_Bin_String[n_bit-2] == '0' && Formatted_Bin_String[n_bit-1] == '0' )
		
				Hex_String[i] = '4';
				
		else if( Formatted_Bin_String[n_bit-4] == '0' && Formatted_Bin_String[n_bit-3] == '0' && 
					Formatted_Bin_String[n_bit-2] == '1' && Formatted_Bin_String[n_bit-1] == '1' )
			
				Hex_String[i] = '3';
		
		else if( Formatted_Bin_String[n_bit-4] == '0' && Formatted_Bin_String[n_bit-3] == '0' && 
					Formatted_Bin_String[n_bit-2] == '1' && Formatted_Bin_String[n_bit-1] == '0' )
		
				Hex_String[i] = '2';
	
		else if( Formatted_Bin_String[n_bit-4] == '0' && Formatted_Bin_String[n_bit-3] == '0' && 
					Formatted_Bin_String[n_bit-2] == '0' && Formatted_Bin_String[n_bit-1] == '1' )
		
				Hex_String[i] = '1';
		
		else if( Formatted_Bin_String[n_bit-4] == '0' && Formatted_Bin_String[n_bit-3] == '0' && 
					Formatted_Bin_String[n_bit-2] == '0' && Formatted_Bin_String[n_bit-1] == '0' )
		
				Hex_String[i] = '0';		
				

	}
	
	return Hex_String;	
}















