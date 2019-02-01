


/*  ------  Header  ------  */


	typedef struct instructions{
					char *INST;
					char *op1;
					char *op2;
					char *OPCode;
					int file_rows;
				} instructions;


	typedef struct Exit_Status{
						char *File_Name;
						int Status;
						} Exit_Status;


	int pot2(int pot);
	int pot16(int pot);
	char *INTtoBIN(int value, int lenght);
	char *BinStringToHexString(char *BinString, int n_chars);
	char *HEXtoBIN(char *Hex_String);
	char *Encode_Instruction(char *inst, char *op1, char *op2);
	char *Hex_Generator(char *OPCode1, char *OPCode2, char *OPCode3, char *OPCode4, char *OPCode5, int hex_count_line);
	char *Byte_SUM(char *A, char *B);
	char *CP2(char *String);
	instructions *Read_File_ASM(char *File_Name, int request);
	Exit_Status *Write_Hex_File(char **OPCode, char *OutputName);
