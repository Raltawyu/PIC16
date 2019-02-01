#include <stdio.h>
#include <stdlib.h>
#include <string.h>




/*  Backlight Color */

#define BckGreen_Bright    "\033[0;102m"
#define BckGreen_Dark      "\033[0;42m"


/*    Text Color    */

#define TxtWhite_Bright    "\033[0;97m"
#define TxtWhite_Dark      "\033[0;37m"

#define TxtBlack_Bright    "\033[0;90m"
#define TxtBlack_Dark      "\033[0;30m"

#define TxtBlue_Bright     "\033[0;94m"
#define TxtBlue_Dark       "\033[0;34m"

#define TxtRed_Bright      "\033[0;91m"
#define TxtRed_Dark        "\033[0;31m"

#define TxtGreen_Bright    "\033[0;92m"
#define TxtGreen_Dark      "\033[0;32m"

#define TxtYellow_Bright   "\033[0;93m"
#define TxtYellow_Dark     "\033[0;33m"

#define TxtPurple_Bright   "\033[0;95m"
#define TxtPurple_Dark     "\033[0;35m"


#define TxtReset           "\33[0;0m"



int main (int argc, char*argv[])
{
		
	char temp_instr[30], temp_char;
	int string_lenght=0, TotNumInstr=0;
	

			

	FILE *fd;							//Open file passed as line input
	fd=fopen(argv[1], "r");

	

	if (fd == NULL)     									//Check file opens correctly								
	{
		printf(TxtRed_Bright "\n\n\n\t\t Error during opening file:"TxtYellow_Bright "  '%s'\n\n\n\n", argv[1]);
		exit(1);
	}
	
	
	
	else
	{
		printf(TxtBlue_Bright "\n\n\n Reading file '%s'..\n", argv[1]);
		printf(TxtReset);
		
			
		while ((fscanf(fd,"%c",&temp_char)) != EOF)		//Counts file lines
		{		
			if(temp_char == '\n') TotNumInstr++;
		}
		
		fseek(fd,0,0);										//Pointing file beginning line
			
		 char **INSTR = (char **)malloc(10*(TotNumInstr-1)*sizeof(char));
		
			
			for (int i= 0; i<TotNumInstr-1; i++)	//Buffering Instructions
			{
				fscanf(fd,"%c",&temp_char); 					//Delete beginning ':'
				
				for (int j=0; temp_char != '\n'; j++)
				{
					fscanf(fd,"%c",&temp_char);
					if (temp_char != '\n') 	temp_instr[j]=temp_char;
					else temp_instr[j]='\0';
				}
				
				string_lenght=strlen(temp_instr);
				
				INSTR[i] = (char*)malloc(2*string_lenght*sizeof(char));
				
				
				if (INSTR[i] == NULL)
					{
						printf(TxtRed_Bright "\n\n\tToo much instructions, not enought memory..\n");
						exit(1);
					}
				else 
					{
						for (int j=0; j<string_lenght; j++)
						{
							INSTR[i][j]=temp_instr[j];
						}
					}						
			}
		
		
		
		
		
		/* --------------------------------------------------- */
		
		
		printf(TxtBlue_Bright " File content:\n");						//Prints file content

		for (int i=0; i<TotNumInstr-1;i++)
		{
			printf (TxtReset"\t\t %-20s\n",INSTR[i]);
		}
		
		
		/* --------------------------------------------------- */
		





		printf ("\n\n\t"BckGreen_Dark "Hex\t\tInstruction" TxtReset "\n\n");   //Print columns
		
		
		for (int i=0; i<TotNumInstr-1; i++)
		{
			short int conv;
			char c[3]={INSTR[i][0],INSTR[i][1], '\0'};
			conv = strtoul(c, NULL, 16);	
			if (conv == 0 ){	
				printf (TxtBlue_Bright"\n\n\n\t---- End Instructions ----\n");	
				printf (TxtGreen_Bright"\n\t   Reading Successfull!\n\n\n\n");
			}
			else if (conv != 0)
				{
				
					for (int j=8; j < conv*2+8; j++)
					{
						char nist[5];//nist serve per memorizzare correttamente la singola istruzione
						nist[0]=INSTR[i][j+2];
						nist[1]=INSTR[i][j+3];
						nist[2]=INSTR[i][j];
						nist[3]=INSTR[i][j+1];
						nist[4]='\0';
									
						printf (TxtBlue_Bright"\t%s", nist);  //Prints Hex Instruction
						
						short int vali=strtoul(nist, NULL, 16);
						short int f=vali&127; 
						short int d=(vali>>7)&1;
						short int b=(vali>>7)&7;
						short int k=vali&255;
						short int ks=vali&2047;
							
							//FIXED INSTRUCTIONS
							if (vali == 0) printf (TxtPurple_Bright"\t\tNOP\n");
							else if (vali == 9) printf (TxtPurple_Bright"\t\tRETFIE\n");
							else if (vali == 100) printf (TxtPurple_Bright"\t\tCLRWDT\n");
						 	else if (vali == 99) printf (TxtPurple_Bright"\t\tSLEEP\n");
							else if (vali == 8) printf (TxtPurple_Bright"\t\tRETURN\n");
							else if (vali == 256) printf (TxtPurple_Bright"\t\tCLRW\n");
							else if (vali == 64) printf (TxtPurple_Bright"\t\tCLRWDT\n");
							else if((vali>>7)== 3) printf (TxtPurple_Bright"\t\tCLRF 0x%02x\n", f);
							else if((vali>>7)== 1) printf (TxtPurple_Bright"\t\tMOVWF 0x%02x\n", f);
							else if((vali>>8)== 2) printf (TxtPurple_Bright"\t\tSUBWF 0x%02x,0x0%x\n", f,d);
							else if((vali>>8)== 7) printf (TxtPurple_Bright"\t\tADDWF 0x%02x,0x0%x\n", f,d);
							else if((vali>>8)== 5) printf (TxtPurple_Bright"\t\tANDWF 0x%02x,0x0%x\n", f,d);
							else if((vali>>8)== 9) printf (TxtPurple_Bright"\t\tCOMF 0x%02x,0x0%x\n", f,d);
							else if((vali>>8)== 3) printf (TxtPurple_Bright"\t\tDECF 0x%02x,0x0%x\n", f,d);
							else if((vali>>8)== 11) printf (TxtPurple_Bright"\t\tDECFSZ 0x%02x,0x0%x\n", f,d);
							else if((vali>>8)== 12) printf (TxtPurple_Bright"\t\tINCF 0x%02x,0x0%x\n", f,d);
							else if((vali>>8)== 15) printf (TxtPurple_Bright"\t\tINCFSZ 0x%02x,0x0%x\n", f,d);
							else if((vali>>8)== 4) printf (TxtPurple_Bright"\t\tIORWF 0x%02x,0x0%x\n", f,d);
							else if((vali>>8)== 8) printf (TxtPurple_Bright"\t\tMOVF 0x%02x,0x0%x\n", f,d);
							else if((vali>>8)== 13) printf (TxtPurple_Bright"\t\tRLF 0x%02x,0x0%x\n", f,d);
							else if((vali>>8)== 12) printf (TxtPurple_Bright"\t\tRRF 0x%02x,0x0%x\n", f,d);
							else if((vali>>8)== 14) printf (TxtPurple_Bright"\t\tSWAPF 0x%02x,0x0%x\n", f,d);
							else if((vali>>8)== 6) printf (TxtPurple_Bright"\t\tXORWF 0x%02x,0x0%x\n", f,d);
							
							//BIT ORIENTED FILE REGISTER OPERATIONS
							else if((vali>>10)== 4) printf (TxtBlue_Bright"\t\tBCF 0x%02x,0x0%x\n", f,b);
							else if((vali>>10)== 5) printf (TxtBlue_Bright"\t\tBSF 0x%02x,0x0%x\n", f,b);
							else if((vali>>10)== 6) printf (TxtBlue_Bright"\t\tBTFSC 0x%02x,0x0%x\n", f,b);
							else if((vali>>10)== 7) printf (TxtBlue_Bright"\t\tBTFSS 0x%02x,0x0%x\n", f,b);
							
							//LITERAL AND CONTROL OPERATION
							else if((vali>>9)== 31) printf (TxtGreen_Bright"\t\tADDLW 0x%02x\n", k);
							else if((vali>>8)== 57) printf (TxtGreen_Bright"\t\tANDLW 0x%02x\n", k);
							else if((vali>>11)== 4) printf (TxtGreen_Bright"\t\tCALL 0x%02x\n", ks);
							else if((vali>>11)== 5) printf (TxtGreen_Bright"\t\tGOTO 0x%02x\n", ks);
							else if((vali>>8)== 56) printf (TxtGreen_Bright"\t\tIORLW 0x%02x\n", k);
							else if((vali>>10)== 12) printf (TxtGreen_Bright"\t\tMOVLW 0x%02x\n", k);
							else if((vali>>10)== 13) printf (TxtGreen_Bright"\t\tRETLW 0x%02x\n", k);
							else if((vali>>9)== 30) printf (TxtGreen_Bright"\t\tSUBLW 0x%02x\n", k);
							else if((vali>>8)== 58) printf (TxtGreen_Bright"\t\tXORLW 0x%02x\n", k);
							else{ 
									printf(TxtYellow_Bright"\t\tUnknown Instruction\n");
									printf(TxtReset);
							}
										
						j=j+3;
					}
				}
					
			
				
			}	
					
	for (int i=0;i<TotNumInstr-1; i++)
	{
		free(INSTR[i]);
	}



}
fclose(fd);
return 0;
}
