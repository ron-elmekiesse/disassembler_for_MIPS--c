/*
	Created by Ron Elmekiesee

	This program is disassembler for 32 bit MIPS architecture, it's supports many of the mips updates but there's still some instruction not supported due to newer updates.

	28.7.2019

*/


#include "utilities.h"

#include "dis_assembling.h"


int main(int argc, char* argv[])
{
	char* file_name = NULL;
	unsigned char* heap_file = NULL;
	unsigned char* text_section_heap = NULL;
	int file_length = 0, text_section_size_bits = 0, i = 0, opcode_table_size = 0;

	
	if (argc != 2)
	{
		printf("Usage: %s <file_name>\n", argv[0]);
		return -1;
	}


	file_name = (char*) malloc(strlen(argv[1]));


	strcpy(file_name, argv[1]);


	file_length = get_file_length(file_name); //getting the length of the file with the null byte


	heap_file = read_file_to_heap(file_name, file_length); //reads file to heap memory


	// checking if the file's architecture is mips
	if (check_file_architecture(heap_file) != 0)
	{
		printf("File given is not for MIPS architecture! \n");
		return -1;
	}


	// getting the text section heap pointer, derefferencing to the size in bits from the function to insert value
	text_section_heap = get_text_section(heap_file, file_length, &text_section_size_bits);


	opcode_table_size = text_section_size_bits / SIZE_OF_OP_CODE; //number of opcodes

	//array of structs in the size of the opcodes numbers
	struct OPCODE opcode_table[opcode_table_size]; //later to make a heap pointer to that array
	

	if (make_opcode_table(text_section_heap, text_section_size_bits, opcode_table, opcode_table_size) != 0) // checking if error accoured
	{
		printf("Problem in making op code table function! \n");
		return -1;
	}

	if (print_opcodes(opcode_table, opcode_table_size) != 0)
	{
		printf("Problem in printing opcodes function! \n");
		return -1;
	}

	
	return 100;
}