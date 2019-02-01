#make -f MakeFile.sh

all: Main

Main: Assembler.o BinaryOutput.o Read_File_ASM.o Encode_Instruction.o HEX_Generator.o HexOutput.o Operations.o WriteFile.o
	gcc -Wall Assembler.o BinaryOutput.o Read_File_ASM.o Encode_Instruction.o HEX_Generator.o HexOutput.o Operations.c WriteFile.o -o AssemblerPic16F6xxA.o	

Assembler.o: Assembler.c Functions.h
	gcc -c Assembler.c -I.
	
Read_File_ASM.o: Read_File_ASM.c Functions.h
	gcc -c Read_File_ASM.c -I.	
	
WriteFile.o: WriteFile.c Functions.h
	gcc -c WriteFile.c -I.	

Encode_Instruction.o: Encode_Instruction.c Functions.h
	gcc -c Encode_Instruction.c -I.	
	
HEX_Generator.o: HEX_Generator.c Functions.h
	gcc -c HEX_Generator.c -I.	

BinaryOutput.o: BinaryOutput.c Functions.h
	gcc -c BinaryOutput.c -I.
	
HexOutput.o:	HexOutput.c Functions.h
	gcc -c HexOutput.c -I.	
	
Operations.o: Operations.c Functions.h
	gcc -c Operations.c -I.	

.PHONY: clean
clean: 
	-rm edit *.o

