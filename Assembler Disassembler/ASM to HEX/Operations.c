


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







		/*  ----- Sum of two Bytes (bit format) -----  */

char *Byte_SUM(char *A, char *B)
{

	char *A_Formatted;
	char *B_Formatted;  
	
	int A_lenght = strlen(A);							
	int B_lenght = strlen(B);	
	int bit_output;						
	
	if(A_lenght > B_lenght)			//A longer than B, right justify B
	{
		bit_output = A_lenght;
			
		A_Formatted = (char *)malloc(A_lenght*sizeof(char));
		if(A_Formatted == NULL)
		{	
			printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
			exit(1);
		}
		B_Formatted = (char *)malloc(A_lenght*sizeof(char));
		if(B_Formatted == NULL)
		{	
			printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
			exit(1);
		}
		
		for(int i=A_lenght; i>=0; --i)
			A_Formatted[i] = A[i]; 
		for(int i=B_lenght, j=A_lenght; j>=0; --i,--j)
		{
			if(i>=0)
				B_Formatted[j] = B[i];
			else
				B_Formatted[j] = '0';	
		}
		
	}
	else if(B_lenght > A_lenght)	//B longer than A, right justify A
	{	
		bit_output = B_lenght;
	
		A_Formatted = (char *)malloc(B_lenght*sizeof(char));
		if(A_Formatted == NULL)
		{	
			printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
			exit(1);
		}
		B_Formatted = (char *)malloc(B_lenght*sizeof(char));
		if(B_Formatted == NULL)
		{	
			printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
			exit(1);
		}
		
		for(int i=B_lenght; i>=0; --i)
			B_Formatted[i] = B[i]; 
		for(int i=B_lenght, j=A_lenght; i>=0; --i,--j)
		{
			if(j>=0)
				A_Formatted[i] = A[j];
			else
				A_Formatted[i] = '0';	
		}
	}	
	else if(B_lenght == A_lenght)		//A same lenght as B, nothing to do
	{
		bit_output = A_lenght;
			
		A_Formatted = (char *)malloc(A_lenght*sizeof(char));
		if(A_Formatted == NULL)
		{	
			printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
			exit(1);
		}
		B_Formatted = (char *)malloc(A_lenght*sizeof(char));
		if(B_Formatted == NULL)
		{	
			printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
			exit(1);
		}	
		
		for(int i=A_lenght; i>=0; --i)
		{
			A_Formatted[i] = A[i];
			B_Formatted[i] = B[i]; 
		}
	}	
	

	char *SumByte = (char *)malloc(bit_output*sizeof(char));		//Sum Operation
	if(SumByte == NULL)
	{
		printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
		exit(1);
	}
	
	for(int i=0; i<bit_output; i++)
		SumByte[i] = '0';
	SumByte[bit_output] = '\0';
		 		
	char *Carry = (char *)malloc(1*sizeof(char));
	Carry[0] = '0'; 
	
	
	
	for(int i=bit_output; i>=0; --i)
	{
		if( A_Formatted[i] == '0' && B_Formatted[i] == '0' && Carry[0] == '0' )
		{
			SumByte[i] = '0';
			Carry[0] = '0';
		}
		else if( A_Formatted[i] == '0' && B_Formatted[i] == '0' && Carry[0] == '1' )
		{
			SumByte[i] = '1';
			Carry[0] = '0';
		}
		else if( A_Formatted[i] == '0' && B_Formatted[i] == '1' && Carry[0] == '0' )
		{
			SumByte[i] = '1';
			Carry[0] = '0';
		}
		else if( A_Formatted[i] == '1' && B_Formatted[i] == '0' && Carry[0] == '0' )
		{
			SumByte[i] = '1';
			Carry[0] = '0';
		}
		
		else if( A_Formatted[i] == '0' && B_Formatted[i] == '1' && Carry[0] == '1' )
		{
			SumByte[i] = '0';
			Carry[0] = '1';
		}
		else if( A_Formatted[i] == '1' && B_Formatted[i] == '0' && Carry[0] == '1' )
		{
			SumByte[i] = '0';
			Carry[0] = '1';
		}	
		else if( A_Formatted[i] == '1' && B_Formatted[i] == '1' && Carry[0] == '0' )
		{
			SumByte[i] = '0';
			Carry[0] = '1';
		}	
		else if( A_Formatted[i] == '1' && B_Formatted[i] == '1' && Carry[0] == '1' )
		{
			SumByte[i] = '1';
			Carry[0] = '1';
		}					
	}

	SumByte[bit_output] = '\0';

	free(Carry);
	free(A_Formatted);
	free(B_Formatted);
	
	return SumByte;
}





		/*  ----- Two's Complement (8 bit string format) -----  */

char *CP2(char *String)
{		
	int String_Lenght = strlen(String);

	char *CP2_Hex_String = (char *)malloc( ((String_Lenght/4)+1)*sizeof(char) );
	if(CP2_Hex_String == NULL)
	{
		printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
		exit(1);
	}
	
	
	for(int i=0; i<String_Lenght; i++)
	{
		if(String[i] == '1')
		{
			String[i] = '0';		
		}
		else if (String[i] == '0')
		{
			String[i] = '1';		
		}	
	}


	CP2_Hex_String = BinStringToHexString(Byte_SUM(String, INTtoBIN(1, String_Lenght)), ((String_Lenght/4)+1));

	return CP2_Hex_String;
}







