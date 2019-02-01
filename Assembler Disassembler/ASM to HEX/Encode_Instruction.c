

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





				/*  -----  1 Operand OPCode Generator -----  */
					
					
char *CreateOpCode(char *Fixed, int fix_bit, char *Bin)
{
	char *string_out = (char *)malloc(14*sizeof(char));
	if(string_out == NULL)
	{
		printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
		exit(1);	
			
	}		
		
	for(int i=0; i<fix_bit; i++)
	{
		string_out[i] = Fixed[i];
	}
	for(int i=fix_bit, j=0; i<14; i++, j++)
	{
		string_out[i] = Bin[j];
	}
	string_out[14] = '\0';
	

 	return string_out;
}





				/*  -----  2 Operand OPCode Generator -----  */


char *CreateOp2Code(char *Fixed, int fix_bit, char *Bin1, int bit_bin1, char *Bin2)			
{
	
	char *string_out = (char *)malloc(14*sizeof(char));
	if(string_out == NULL)
	{
		printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
		exit(1);	
			
	}		
	
	for(int i=0; i<fix_bit; i++)
	{
		string_out[i] = Fixed[i];
	}			
	for(int i=fix_bit, j=0; i<fix_bit+bit_bin1; i++, j++)
	{
		string_out[i] = Bin1[j];
	}
	for(int i=fix_bit+bit_bin1, j=0; i<14; i++, j++)
	{
		string_out[i] = Bin2[j];
	}
	string_out[14] = '\0';			
				
				
	return string_out;						
}

			
			






				/*  ---------- Encode Instruction ----------  */
				



char *Encode_Instruction(char *inst, char *op1, char *op2)
{

	
	char ADDWF[6] = 	"ADDWF";
	char ANDWF[6] = 	"ANDWF";
	char CLRF[5] = 	"CLRF";
	char CLRW[5] =		"CLRW";
	char COMF[5]= 		"COMF";
	char DECF[5]= 		"DECF";
	char DECFSZ[7]= 	"DECFSZ";
	char INCF[5]= 		"INCF";
	char INCFSZ[7]=	"INCFSZ";
	char IORWF[6]=		"IORWF";
	char MOVF[5]=		"MOVF";
	char MOVWF[6]=		"MOVWF";
	char NOP[4]=		"NOP";
	char RLF[4]=		"RLF";
	char RRF[4]=		"RRF";
	char SUBWF[6]=		"SUBWF";
	char SWAPF[6]=		"SWAPF";
	char XORWF[6]=		"XORWF";
	char BCF[4]=		"BCF";
	char BSF[4]=		"BSF";
	char BTFSC[6]=		"BTFSC";
	char BTFSS[6]=		"BTFSS";
	char ADDLW[6]=		"ADDLW";
	char ANDLW[6]=		"ANDLW";
	char CALL[5]=		"CALL";
	char CLRWDT[7]=	"CLRWDT";
	char GOTO[5]=		"GOTO";
	char IORLW[6]=		"IORLW";
	char MOVLW[6]=		"MOVLW";
	char RETFIE[7]=	"RETFIE";
	char RETLW[6]=		"RETLW";
	char RETURN[7]=	"RETURN";
	char SLEEP[6]=		"SLEEP";
	char SUBLW[6]=		"SUBLW";
	char XORLW[6]=		"XORLW";
	char END[4]=		"END";


		

		unsigned int conv=0, conv1=0;
		char *OPCode = (char *)malloc(15*sizeof(char));
		if(OPCode == NULL)
		{
			printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
			exit(1);	
			
		}
		
		
		
				/*  ----- Decoding Operand 1 -----  */
			
		
		
			if (op1 != NULL)
			{
				if (op1[0] == '.') 							// Check Hex or Decimal
				{
					for (int j=0; op1[j] != '\0'; j++)
					{
						op1[j]=op1[j+1];
					}
					conv=strtol(op1, NULL, 10);
				}
				else if ((op1[0] == '0') && (op1[1] == 'x'))
				{ 
					conv=strtol(op1, NULL, 16);
				}	
			}
			else
			{
				conv=0;
			}
		
		
		
				/*  ----- Decoding Operand 2 -----  */
										
										
		
			if (op2 != NULL)
			{
				if (op2[0] == '.') 
				{
					for (int j=0; op2[j] != '\0'; j++) 
					{
						op2[j]=op2[j+1];
					}
					conv1=strtoul(op2, NULL, 10);			
				}
				else if ((op2[0] == '0') && (op2[1] == 'x')) 
				{
					conv1=strtoul(op2, NULL, 16);		
				}
			}
			else
			{
				conv1 = 0;
			}
			
			
			
				/*  ----- Coding OPCode PIC16F6xxA -----  */
			
			
			char *Bin1 = (char *)malloc(10*sizeof(char));
			if(Bin1 == NULL)
			{
				printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
				exit(1);		
			}
			
			char *Bin2 = (char *)malloc(10*sizeof(char));
			if(Bin2 == NULL)
			{
				printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
				exit(1);		
			}
			
			char *OpString = (char *)malloc(10*sizeof(char));
			if(OpString == NULL)
			{
				printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
				exit(1);		
			}
			
			
			if (strcmp( inst , ADDLW ) == 0) 
			{ 
					OpString = "111110";
					Bin1 = INTtoBIN(conv, 8);
					OPCode = CreateOpCode(OpString, 6, Bin1);   
			}
			else if (strcmp( inst , ANDLW ) == 0) 
			{ 
					OpString = "111001";
					Bin1 = INTtoBIN(conv, 8);
					OPCode = CreateOpCode(OpString, 6, Bin1);  
			}
			else if (strcmp( inst , CALL ) == 0) 
			{
				if (conv <= 2047)
				{ 
					OpString = "100";
					Bin1 = INTtoBIN(conv, 11);
					OPCode = CreateOpCode(OpString, 3, Bin1);  
				}	 
				else
				{  
					printf (RedTxt"\n\t ERROR: Value too high in instruction %s", inst);
					exit(1);
				}
			}
			else if (strcmp( inst , CLRWDT ) == 0) 
					OPCode = "00000001100100";
			else if (strcmp( inst , GOTO ) == 0) 
			{
				if (conv <= 2047)
				{
					OpString = "101";
					Bin1 = INTtoBIN(conv,11);
					OPCode = CreateOpCode(OpString, 3, Bin1);  
				}	
				else  
					printf (RedTxt"\n\t ERROR: Value too high in instruction %s", inst);
			}	
			else if (strcmp( inst , IORLW ) == 0)
			{
					OpString = "111000";
					Bin1 = INTtoBIN(conv, 8);
					OPCode = CreateOpCode(OpString, 6, Bin1);  
			}		
			else if (strcmp( inst , MOVLW ) == 0)
			{
					OpString = "110000";
					Bin1 = INTtoBIN(conv, 8);
					OPCode = CreateOpCode(OpString, 6, Bin1);  
			}
			else if (strcmp( inst , RETFIE ) == 0) 
					OPCode = "00000000001001";
			else if (strcmp( inst , RETLW ) == 0)
			{
					OpString = "110100";
					Bin1 = INTtoBIN(conv, 8);
					OPCode = CreateOpCode(OpString, 6, Bin1);  
			}		
			else if (strcmp( inst , RETURN ) == 0) 
					OPCode = "00000000001000";
			else if (strcmp( inst, SLEEP ) == 0) 
					OPCode = "00000001100011";
			else if (strcmp( inst , SUBLW ) == 0)
			{ 
				OpString = "111100";
				Bin1 = INTtoBIN(conv, 8);
				OPCode = CreateOpCode(OpString, 6, Bin1);
			}
			else if (strcmp( inst , XORLW ) == 0)
			{ 
				OpString = "111010";
				Bin1 = INTtoBIN(conv, 8);
				OPCode = CreateOpCode(OpString, 6, Bin1);
			}
	
	
	
	
			//BYTE-ORIENTED FILE REGISTER OPERATIONS
	
	
	
	
			else if (strcmp( inst , ADDWF ) == 0)
			{ 
					char OpString[] = "000111";
					char *Bin1 = INTtoBIN(conv1, 1);
					char *Bin2 = INTtoBIN(conv, 7);
					OPCode = CreateOp2Code(OpString, 6, Bin1, 1, Bin2);			
			}
			else if (strcmp( inst , ANDWF ) == 0)
			{ 
					OpString = "000101";
					Bin1 = INTtoBIN(conv1, 1);
					Bin2 = INTtoBIN(conv, 7);
					OPCode = CreateOp2Code(OpString, 6, Bin1, 1, Bin2);
			}
			else if (strcmp( inst , CLRF ) == 0)
			{ 					
					OpString = "0000011";
					Bin1 = INTtoBIN(conv, 7);
					OPCode = CreateOpCode(OpString, 7, Bin1);
			}
			else if (strcmp( inst , CLRW ) == 0) 
					OPCode = "00000100000000";
			else if (strcmp( inst , COMF ) == 0)
			{ 
					OpString = "001001";
					Bin1 = INTtoBIN(conv1, 1);
					Bin2 = INTtoBIN(conv, 7);
					OPCode = CreateOp2Code(OpString, 6, Bin1, 1, Bin2);
			}
			else if (strcmp( inst , DECF ) == 0)
			{ 
					OpString = "000011";
					Bin1 = INTtoBIN(conv1, 1);
					Bin2 = INTtoBIN(conv, 7);
					OPCode = CreateOp2Code(OpString, 6, Bin1, 1, Bin2);
			}
			else if (strcmp( inst , DECFSZ) == 0)
			{ 
					OpString = "001011";
					Bin1 = INTtoBIN(conv1, 1);
					Bin2 = INTtoBIN(conv, 7);
					OPCode = CreateOp2Code(OpString, 6, Bin1, 1, Bin2);
			}
			else if (strcmp( inst , INCF ) == 0)
			{ 
					OpString = "001010";
					Bin1 = INTtoBIN(conv1, 1);
					Bin2 = INTtoBIN(conv, 7);
					OPCode = CreateOp2Code(OpString, 6, Bin1, 1, Bin2);
			}
			else if (strcmp( inst , INCFSZ ) == 0)
			{ 
					OpString = "001111";
					Bin1 = INTtoBIN(conv1, 1);
					Bin2 = INTtoBIN(conv, 7);
					OPCode = CreateOp2Code(OpString, 6, Bin1, 1, Bin2);
			}
			else if (strcmp( inst , IORWF ) == 0)
			{ 
					OpString = "000100";
					Bin1 = INTtoBIN(conv1, 1);
					Bin2 = INTtoBIN(conv, 7);
					OPCode = CreateOp2Code(OpString, 6, Bin1, 1, Bin2);
			}
			else if (strcmp( inst , MOVF ) == 0)
			{ 
					OpString = "001000";
					Bin1 = INTtoBIN(conv1, 1);
					Bin2 = INTtoBIN(conv, 7);
					OPCode = CreateOp2Code(OpString, 6, Bin1, 1, Bin2);
			}	
			else if (strcmp( inst , MOVWF ) == 0)
			{   
					OpString = "0000001";
					Bin1= INTtoBIN(conv, 7);
					OPCode = CreateOpCode(OpString, 7, Bin1);			
			}
			else if (strcmp( inst , NOP ) == 0) 
					OPCode = "00000000000000";
			else if (strcmp( inst , RLF ) == 0)
			{ 
					OpString = "001101";
					Bin1 = INTtoBIN(conv1, 1);
					Bin2 = INTtoBIN(conv, 7);
					OPCode = CreateOp2Code(OpString, 6, Bin1, 1, Bin2);
			}
			else if (strcmp( inst , RRF ) == 0)
			{ 
					OpString = "001100";
					Bin1 = INTtoBIN(conv1, 1);
					Bin2 = INTtoBIN(conv, 7);
					OPCode = CreateOp2Code(OpString, 6, Bin1, 1, Bin2);
			}
			else if (strcmp( inst , SUBWF ) == 0)
			{ 
					OpString = "000010";
					Bin1 = INTtoBIN(conv1, 1);
					Bin2 = INTtoBIN(conv, 7);
					OPCode = CreateOp2Code(OpString, 6, Bin1, 1, Bin2);
			}
			else if (strcmp( inst , SWAPF ) == 0)
			{ 
					OpString = "001110";
					Bin1 = INTtoBIN(conv1, 1);
					Bin2 = INTtoBIN(conv, 7);
					OPCode = CreateOp2Code(OpString, 6, Bin1, 1, Bin2);
			}
			else if (strcmp( inst , XORWF ) == 0)
			{ 
					OpString = "000110";
					Bin1 = INTtoBIN(conv1, 1);
					Bin2 = INTtoBIN(conv, 7);
					OPCode = CreateOp2Code(OpString, 6, Bin1, 1, Bin2);
			}
	
	
	
	
	
			//BIT-ORIENTED FILE REGISTER OPERATIONS
	
			
			
			
			
			else if (strcmp( inst , BCF ) == 0)
			{ 
					OpString = "0100";
					Bin1 = INTtoBIN(conv1, 3);
					Bin2 = INTtoBIN(conv, 7);
					OPCode = CreateOp2Code(OpString, 4, Bin1, 3, Bin2);
			}
			else if (strcmp( inst , BSF ) == 0)
			{ 
					OpString = "0101";
					Bin1 = INTtoBIN(conv1, 3);
					Bin2 = INTtoBIN(conv, 7);
					OPCode = CreateOp2Code(OpString, 4, Bin1, 3, Bin2);
			}
			else if (strcmp( inst , BTFSC ) == 0)
			{ 
					OpString = "0110";
					Bin1 = INTtoBIN(conv1, 3);
					Bin2 = INTtoBIN(conv, 7);
					OPCode = CreateOp2Code(OpString, 4, Bin1, 3, Bin2);
			}
			else if (strcmp( inst , BTFSS ) == 0)
			{
					OpString = "0111";
					Bin1 = INTtoBIN(conv1, 3);
					Bin2 = INTtoBIN(conv, 7);
					OPCode = CreateOp2Code(OpString, 4, Bin1, 3, Bin2);
			}	
		 		
	
	
	
	
	return OPCode;

}





