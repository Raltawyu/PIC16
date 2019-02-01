#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Functions.h"



#define InstrColor 	"\033[0;94m"
#define OPColor 		"\033[0;95m"
#define TxtReset		"\033[0;0m"  
#define OrangeTxt		"\033[0;33m"
#define MagentaTxt	"\033[0;96m"	
#define GreenTxt		"\033[0;92m"
#define RedTxt			"\033[0;91m"







	/*	--------------------		MAIN		-----------------------	*/






int main (int argc, char *argv[])
{

									
									
										/*  ----- Reading File ASM -----  */
										



		printf(MagentaTxt"\n\n\n\tOpening file: %s", argv[1]);
		printf(MagentaTxt"\n\n\tASM instructions:	");				
		
		int num_instructions = (int) Read_File_ASM(argv[1], 1);				
		
		instructions *File_Read = (instructions *)calloc(num_instructions+1,sizeof(instructions));
		if(File_Read == NULL)
		{
			printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
			exit(1);
		}
		File_Read = Read_File_ASM(argv[1], 0);   		//Saves struct pointer in return from Read_File_ASM function 

		for (int i=0; i<num_instructions-3; i++)
		{
			File_Read[i].INST = Read_File_ASM(argv[1], 0)[i].INST;
			File_Read[i].op1 = Read_File_ASM(argv[1], 0)[i].op1;
			File_Read[i].op2 = Read_File_ASM(argv[1], 0)[i].op2;
		}



		printf("\n\n");
		for (int i=0; i<num_instructions-3; i++)
		{
			printf ("\n\t"InstrColor"%-20s"TxtReset, File_Read[i].INST);
			if(File_Read[i].op1 != NULL)
				printf ("\t"OPColor"%-20s"TxtReset, File_Read[i].op1);
			if(File_Read[i].op2 != NULL)
				printf ("\t"OPColor"%-20s"TxtReset"", File_Read[i].op2);
		}
			
		
		
		
		
		
										/*  ----- Coding Operations PIC16F6xxA-----  */
		
		
		
		
		
		printf(MagentaTxt "\n\n\tCoding assembly for PIC16F6xxA...\n");
		printf(GreenTxt);

		char *OPCode = (char *)malloc(15*sizeof(char)); 
		if(OPCode == NULL)
		{
			printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
			exit(1);	
		}
				
		for (int i=0; i<num_instructions-3; i++)
		{
			File_Read[i].OPCode = Encode_Instruction(File_Read[i].INST, File_Read[i].op1, File_Read[i].op2);
			printf(OrangeTxt"\n\t\t%s", File_Read[i].OPCode);
		}

		
		
		char **HEX_Code_Line = (char **)calloc( (num_instructions/5)+1,sizeof(char) );
			for(int i=0; i<((num_instructions/5)+1) ; i++)
			{
				HEX_Code_Line[i] = (char *)calloc(32,sizeof(char));
			}	
		
		if(HEX_Code_Line == NULL)
		{	
			printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
			exit(1);	
		}
						
		
		
		
		
		
		
		
		/*
		//Da eliminare, di test!!
		
		HEX_Code_Line[0] = Hex_Generator(File_Read[5].OPCode, File_Read[6].OPCode, 
													File_Read[7].OPCode, File_Read[8].OPCode, 
													File_Read[9].OPCode, 5 );
		
		printf("\n\nStringa convertita:   %s\n\n", HEX_Code_Line[0]);
		*/
				
				
		for(int instruction=0, LineCode=0; instruction<=num_instructions-1; instruction+=5, LineCode++)
		{	
			if( File_Read[instruction+4].OPCode == NULL )			 //Case there are less then 5 operands remaining
			{
				if( File_Read[instruction+3].OPCode == NULL )
				{
					if( File_Read[instruction+2].OPCode == NULL )
					{
						if( File_Read[instruction+1].OPCode == NULL )
						{
							if( File_Read[instruction].OPCode == NULL )		
							{
								HEX_Code_Line[LineCode] = Hex_Generator(NULL, NULL, NULL, NULL, NULL, instruction); 
							}
							else
							{
								HEX_Code_Line[LineCode] = Hex_Generator(File_Read[instruction].OPCode, NULL, NULL, NULL, NULL, instruction); 	
							}	
						}
						else
						{
							HEX_Code_Line[LineCode] = Hex_Generator(File_Read[instruction].OPCode, 
																				 File_Read[instruction+1].OPCode, NULL, NULL, NULL, instruction); 		
						}
					}
					else
					{
						HEX_Code_Line[LineCode] = Hex_Generator(File_Read[instruction].OPCode, 
																			 File_Read[instruction+1].OPCode, 
																			 File_Read[instruction+2].OPCode, NULL, NULL, instruction); 		
					}
				}		
				else
				{
					HEX_Code_Line[LineCode] = Hex_Generator(File_Read[instruction].OPCode, 
																		 File_Read[instruction+1].OPCode, 
																		 File_Read[instruction+2].OPCode, 
																		 File_Read[instruction+3].OPCode, NULL, instruction); 
				}
			}
			else	
			{
				HEX_Code_Line[LineCode] = Hex_Generator(File_Read[instruction].OPCode, 
																	 File_Read[instruction+1].OPCode, 
																  	 File_Read[instruction+2].OPCode, 
																  	 File_Read[instruction+3].OPCode, 
												   		  	 	 File_Read[instruction+4].OPCode, instruction);												
		
			}		
			
			HEX_Code_Line[LineCode+1] = Hex_Generator(NULL, NULL, NULL, NULL, NULL, instruction); 		
		}
		
		
		
		
		//Clear Memory
		
		for (int i=0;i<num_instructions-3; i++)
		{
			free(File_Read[i].INST);
			free(File_Read[i].op1);	
			free(File_Read[i].op2);
		}
	
		
			
		time_t start_write_time = time(NULL);		
		printf(MagentaTxt"\n\n\t");
		printf(ctime(&start_write_time));
		
		printf(MagentaTxt"\tWriting OPCode... \n");
		for(int i=0; i<(num_instructions/5)+1 ;i++)
		{
			printf("\n\t%s", HEX_Code_Line[i]);	
		}
		printf("\n");
		
		
		char *OutputFileName = "PIC16F6xxA_BitStream";
		Exit_Status *ReturnStatus = (Exit_Status *)malloc(1*sizeof(Exit_Status));
		ReturnStatus = Write_Hex_File(HEX_Code_Line, OutputFileName);
		
		if(ReturnStatus[0].Status == 1)
		{
			printf(MagentaTxt"\n\n\t------------------------------------------------------- ");
			printf(GreenTxt"\n\n\t Successfull writing"InstrColor" %s"GreenTxt" file", ReturnStatus[0].File_Name);
			start_write_time = time(NULL);	
			printf("\n\t End on:  ");
			printf(ctime(&start_write_time));
			printf(MagentaTxt "\n\t Pierpaolo Granello 1571747  -- PIC16F6xxA Assembler 15/01/2018");
			printf(MagentaTxt "\n\t Digital Systems Programming -- Prof. Antonio Mastrandrea"); 
			printf(MagentaTxt "\n\t Laurea Magistrale Ing. Elettronica \"La Sapienza\" ");
		}
		else if(ReturnStatus[0].Status == 0)
		{
			printf(RedTxt"\n\n\n\n\t\tError writing output"InstrColor" %s file", ReturnStatus[0].File_Name);
			start_write_time = time(NULL);	
			printf("\n\t\tFinish with errors on:  ");
			printf(ctime(&start_write_time));
			printf("\n");
		}
	
	
		
		
		
		
	printf("\n\n\n\n");	
	
	return 0;
}









