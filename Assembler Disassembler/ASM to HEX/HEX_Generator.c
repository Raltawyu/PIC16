


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



		/*  ----- Hexadecimal Address Calculator  -----  */

char *StartAddress(int hex_count_line)
{
		char *HEX_Address = (char *)malloc(5*sizeof(char));
		if(HEX_Address == NULL)
		{
			printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
			exit(1);
		}
		
		HEX_Address = BinStringToHexString( INTtoBIN(hex_count_line, 16), 4 );
	
		return HEX_Address;
}



		/*  ----- Checksum Calculator  -----  */

char *Checksum_Generator(char *String)							//String is Hexadecimal Type	
{
	char *GeneratedChecksum = (char *)malloc(3*sizeof(char));
	if(GeneratedChecksum == NULL)
	{
		printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
		exit(1);
	}
	GeneratedChecksum[2] = '\0';
	
	char *temp_Byte = (char *)malloc(3*sizeof(char));
	if(temp_Byte == NULL)
	{
		printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
		exit(1);
	}
	temp_Byte[2] = '\0';
	
	GeneratedChecksum[1] = String[strlen(String)-1];
	GeneratedChecksum[0] = String[strlen(String)-2]; 
	
	for(int i=strlen(String)-3; i>1; i-=2)
	{
		temp_Byte[1] = String[i];
		temp_Byte[0] = String[i-1];
		GeneratedChecksum = BinStringToHexString(Byte_SUM(HEXtoBIN(GeneratedChecksum), HEXtoBIN(temp_Byte)),2); 
	}

	free(temp_Byte);


	return GeneratedChecksum;
} 








							/*  ----- Hex_Generator Function -----  */


char *Hex_Generator(char *OPCode1, char *OPCode2, char *OPCode3, char *OPCode4, char *OPCode5, int hex_count_line)
{
		
		
		//hex_count_line riporta il conto dei richiami della funzione, per indicizzare la memoria programma


		
		char *temp_string = (char *)malloc(4*sizeof(char));
		if(temp_string == NULL)
		{
			printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
			exit(1);	
		}

		char *NumberOfBytes = (char *)malloc(2*sizeof(char));
		if(NumberOfBytes == NULL)
		{
			printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
			exit(1);	
		}

		char *ProgMemStartAddrress = (char *)malloc(5*sizeof(char));
		if(ProgMemStartAddrress == NULL)
		{
			printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
			exit(1);	
		}
		
		
		char *Checksum = (char *)malloc(2*sizeof(char));
		if(Checksum == NULL)
		{
			printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
			exit(1);	
		}
		
		char *Hex_Code_Line = (char *)malloc(32*sizeof(char));
		if(Hex_Code_Line == NULL)
		{
			printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
			exit(1);	
		}

		
		
		ProgMemStartAddrress = StartAddress(hex_count_line);	//Start Address Hex Conversion
		Hex_Code_Line[3] = ProgMemStartAddrress[0];
		Hex_Code_Line[4] = ProgMemStartAddrress[1];
		Hex_Code_Line[5] = ProgMemStartAddrress[2];
		Hex_Code_Line[6] = ProgMemStartAddrress[3];		

		Hex_Code_Line[7] = '0';		//HEX Type: DATA
		Hex_Code_Line[8] = '0';		



		if(OPCode1 != NULL)
		{
			Hex_Code_Line[0] = ':'; 
		
			Hex_Code_Line[1] = '0';
			Hex_Code_Line[2] = '2';		//There are 2 DataBytes
			
			temp_string = BinStringToHexString(OPCode1, 4); 
			Hex_Code_Line[9] = temp_string[2];
			Hex_Code_Line[10] = temp_string[3];
			Hex_Code_Line[11] = temp_string[0];
			Hex_Code_Line[12] = temp_string[1];	
			
			Checksum = Checksum_Generator(Hex_Code_Line);
			Hex_Code_Line[13] = Checksum[0];
			Hex_Code_Line[14] = Checksum[1];	//ChecksumEndLine		
			
			Hex_Code_Line[15] = '\0';			//End String
		}	
		
		if(OPCode2 != NULL)
		{
			Hex_Code_Line[0] = ':'; 
			
			Hex_Code_Line[1] = '0';
			Hex_Code_Line[2] = '4';		//There are 4 DataBytes
		
			temp_string = BinStringToHexString(OPCode2, 4); 
			Hex_Code_Line[13] = temp_string[2];
			Hex_Code_Line[14] = temp_string[3];
			Hex_Code_Line[15] = temp_string[0];
			Hex_Code_Line[16] = temp_string[1];
			
			Checksum = Checksum_Generator(Hex_Code_Line);
			Hex_Code_Line[17] = Checksum[0];
			Hex_Code_Line[18] = Checksum[1];	//ChecksumEndLine		
			
			Hex_Code_Line[19] = '\0';			//End String
		
		}
			
		if(OPCode3 != NULL)
		{
			Hex_Code_Line[0] = ':'; 
			
			Hex_Code_Line[1] = '0';
			Hex_Code_Line[2] = '6';		//There are 6 DataBytes
			
			temp_string = BinStringToHexString(OPCode3, 4); 
			Hex_Code_Line[17] = temp_string[2];
			Hex_Code_Line[18] = temp_string[3];
			Hex_Code_Line[19] = temp_string[0];
			Hex_Code_Line[20] = temp_string[1];
			
			Checksum = Checksum_Generator(Hex_Code_Line);
			Hex_Code_Line[21] = Checksum[0];
			Hex_Code_Line[22] = Checksum[1];	//ChecksumEndLine		
			
			Hex_Code_Line[23] = '\0';			//End String
		}
			
		if(OPCode4 != NULL)
		{
			Hex_Code_Line[0] = ':'; 
			
			Hex_Code_Line[1] = '0';
			Hex_Code_Line[2] = '8';		//There are 8 DataBytes
			
			temp_string = BinStringToHexString(OPCode4, 4);
			Hex_Code_Line[21] = temp_string[2];
			Hex_Code_Line[22] = temp_string[3];
			Hex_Code_Line[23] = temp_string[0];
			Hex_Code_Line[24] = temp_string[1];
			
			Checksum = Checksum_Generator(Hex_Code_Line);
			Hex_Code_Line[25] = Checksum[0];
			Hex_Code_Line[26] = Checksum[1];	//ChecksumEndLine		
			
			Hex_Code_Line[27] = '\0';			//End String
		}
			
		if(OPCode5 != NULL)
		{
			Hex_Code_Line[0] = ':'; 
		
			Hex_Code_Line[1] = '0';
			Hex_Code_Line[2] = 'A';		//There are 10 DataBytes
		
			temp_string = BinStringToHexString(OPCode5, 4);
			Hex_Code_Line[25] = temp_string[2];
			Hex_Code_Line[26] = temp_string[3];
			Hex_Code_Line[27] = temp_string[0];
			Hex_Code_Line[28] = temp_string[1];
			
			Checksum = Checksum_Generator(Hex_Code_Line);
			Hex_Code_Line[29] = Checksum[0];
			Hex_Code_Line[30] = Checksum[1];	//ChecksumEndLine		
			
			Hex_Code_Line[31] = '\0';			//End String
		}
		
		if(OPCode1 == NULL && OPCode2 == NULL && OPCode3 == NULL && OPCode4 == NULL && OPCode5 == NULL)
		{
			Hex_Code_Line[0] = ':';
			 
			Hex_Code_Line[1] = '0';
			Hex_Code_Line[2] = '0';		//There are 0 DataBytes
			
			Hex_Code_Line[7] = '0';
			Hex_Code_Line[8] = '1';    //End Of File
			
			Hex_Code_Line[9] = '\0';	
			
			Checksum = Checksum_Generator(Hex_Code_Line);
			Hex_Code_Line[9] = Checksum[0];
			Hex_Code_Line[10] = Checksum[1];	//ChecksumEndLine		
			
			Hex_Code_Line[11] = '\0';			//End String
			
			return Hex_Code_Line;
		}	

		
		
	
		free(temp_string);
		free(NumberOfBytes);
		free(ProgMemStartAddrress);
		free(Checksum);	
		
		return Hex_Code_Line;

}






