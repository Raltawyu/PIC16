

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





		/*  ----- Writes Output File  -----  */		

Exit_Status *Write_Hex_File(char **OPCode, char *OutputName)
{
	
	
	Exit_Status *ReturnStatus = (Exit_Status *)malloc(1*sizeof(Exit_Status));

	int Original_Name_Lenght = strlen(OutputName);
	ReturnStatus[0].File_Name = (char *)malloc((Original_Name_Lenght+6)*sizeof(char));
	ReturnStatus[0].Status = 0;
	
	for(int i=0; OutputName[i] != '\0'; i++)
	{
		ReturnStatus[0].File_Name[i] = OutputName[i];
	}
	ReturnStatus[0].File_Name[Original_Name_Lenght] = '.';
	ReturnStatus[0].File_Name[Original_Name_Lenght+1] = 'h';
	ReturnStatus[0].File_Name[Original_Name_Lenght+2] = 'e';
	ReturnStatus[0].File_Name[Original_Name_Lenght+3] = 'x';
	ReturnStatus[0].File_Name[Original_Name_Lenght+4] = '\0';
	
	
	FILE *fd;							/*  Checking if file already exists  */
	
	for(int Name_Buffer=1; fd=fopen(ReturnStatus[0].File_Name, "r"); Name_Buffer++) //Creating new name for file to be created
	{
		fclose(fd);
		
		char *NameCount = (char *)malloc(5*sizeof(char));	
		NameCount = BinStringToHexString(INTtoBIN(Name_Buffer, 8), 2);
		
		ReturnStatus[0].File_Name[Original_Name_Lenght] = NameCount[0];
		ReturnStatus[0].File_Name[Original_Name_Lenght+1] = NameCount[1];
		ReturnStatus[0].File_Name[Original_Name_Lenght+2] = '.';
		ReturnStatus[0].File_Name[Original_Name_Lenght+3] = 'h';
		ReturnStatus[0].File_Name[Original_Name_Lenght+4] = 'e';
		ReturnStatus[0].File_Name[Original_Name_Lenght+5] = 'x';
		ReturnStatus[0].File_Name[Original_Name_Lenght+6] = '\0';
	
		free(NameCount);
		if(Name_Buffer == 5)
			break;
	}
	
	
	
	fd = fopen(ReturnStatus[0].File_Name, "w");
	if(fd == NULL) 
	{
		printf (RedTxt"\n\n\n\t\tError creating file: %s", ReturnStatus[0].File_Name);
		return ReturnStatus[0].Status;
	}
	
	

	for(int i=0; ; i++)
	{	
		if(OPCode[i] == '\0')
			break;
		for(int j=0; ; j++)
		{	
			if(OPCode[i][j] == '\0')
				break;
			fprintf(fd, "%c",OPCode[i][j]);
		}
		fprintf(fd, "\n");
	}
	fclose(fd);

		/*  ----- Checking File is correct -----  */

	fd = fopen(ReturnStatus[0].File_Name, "r");
	char temp_char;
	for(int i=0; fscanf(fd, "%c", &temp_char) != EOF; i++)
	{
		if(OPCode[i] == '\0')
			break;
		for(int j=0; OPCode[i][j] != '\0'; j++)
		{	
				if(temp_char != OPCode[i][j])
					return ReturnStatus;
				
				fscanf(fd, "%c", &temp_char);
		}
	}
	
	fclose(fd);
	
	
	fd = fopen(ReturnStatus[0].File_Name, "a");
	fprintf(fd, "\n\n\n\n\t Pierpaolo Granello 1571747  -- PIC16F6xxA Assembler 15/01/2018");
	fprintf(fd, "\n\t Digital Systems Programming -- Prof. Antonio Mastrandrea"); 
	fprintf(fd, "\n\t Laurea Magistrale Ing. Elettronica \"La Sapienza\" ");
	
	time_t start_write_time = time(NULL);		
	fprintf(fd,ctime(&start_write_time));

	fclose(fd);

	ReturnStatus[0].Status = 1;	

	return ReturnStatus;
}






