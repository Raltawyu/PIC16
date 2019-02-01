

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h" 


#define InstrColor 	"\033[0;94m"
#define OPColor 		"\033[0;95m"
#define TxtReset		"\033[0;0m"  
#define MagentaTxt	"\033[0;96m"	
#define GreenTxt		"\033[0;92m"
#define RedTxt			"\033[0;91m"


	/*  ----- Reading file operation-----  */
	
	
	instructions *Read_File_ASM(char *File_Name, int request)			//request=1 returns number of instruction
	{																						//request=0 returns instructions
	
		char ch, p;
		char temp_string1[100], temp_string2[100], temp_string3[100];
		int lenght_string1=0, lenght_string2=0, lenght_string3=0, file_rows=0;
		
		
		FILE *fd;
		fd=fopen(File_Name, "r");

		if (fd == NULL) 
		{
			printf (RedTxt"\n\n\n\t\tError opening file: %s", File_Name);
			exit(1);
		}
		
		
		while ((fscanf(fd,"%c",&ch)) != EOF)   //Counts file rows
		{		
			if(ch == '\n') file_rows++;
		}
				
		fseek(fd,0,0);
		
		instructions *INST = (instructions*)malloc(file_rows*sizeof(instructions)); //Allocates *INST struct
		if(INST == NULL)
		{
			printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
		}
	
	
		if(request == 1)
		{
			return file_rows;
		}
		
	
		char *line = (char *)malloc(128 * sizeof(char));
	
		size_t len;
	
		for(int i = 0; i<2; i++)
		{ 
			getline(&line, &len, fd);
		}
		
		for(int i= 0; i<file_rows-3; i++)
		{               
				fscanf(fd,"%c",&ch);     
				
				for (int j=0; j<100 ; j++)
				{
					fscanf(fd,"%c",&ch); 
					if (ch == ' ')						//To jump initial TAB
					{
						temp_string1[j]= '\0';
						break;	
					}			
					else 
					{
						temp_string1[j]= ch;
					}		
				}
				
				lenght_string1=strlen(temp_string1);
				INST[i].INST=(char*)malloc(lenght_string1*sizeof(char));
				
				if (INST[i].INST == NULL)
				{
					printf("\n\n\n\t\tNot enough memory\n\n\n");
					exit(1);
				}
				else 
				{	
					for (int j=0; j < lenght_string1; j++)
					{
						INST[i].INST[j]=temp_string1[j];
					}
				}
				
				for (int j=0; j<100 ; j++)
				{
					fscanf(fd,"%c",&ch); 
					if ((ch =='\n') || (ch ==','))
						{
							temp_string2[j]='\0';
							p=ch;
							break;				
						}						
						else 
						{
							temp_string2[j]= ch;
						}		

				}
				
				lenght_string2=strlen(temp_string2);
				
				INST[i].op1=(char*)malloc(lenght_string2*sizeof(char));
				if(INST[i].op1 == NULL)
				{
					printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
					exit(1);
				}				
				else 
				{
					for (int j=0; j < lenght_string2; j++)
					{
						INST[i].op1[j]=temp_string2[j];
					}
				}
		
				if (p == ',')									//If the operation is on 2 registers
				{
					for (int j=0; j<100 ; j++)
					{
						fscanf(fd,"%c",&ch); 
						if (ch =='\n')
						{
							temp_string3[j]='\0';
							break;				
						}						
						else 
						{
							temp_string3[j]= ch;
						}		

					}
				
					lenght_string3=strlen(temp_string3);
					INST[i].op2=(char*)malloc(lenght_string3*sizeof(char));
					if(INST[i].op1 == NULL)
					{
						printf(RedTxt"\n\n\t\tNot enough memory\n\n\n");
						exit(1);
					}
					else
					{
						for (int j=0; j < lenght_string3; j++)
						{
							INST[i].op2[j]=temp_string3[j];
						}
					}
				}
				else INST[i].op2=NULL;								//Else on 1 register
		}
		
	
		fclose(fd);
		
		
		return INST;
	
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
