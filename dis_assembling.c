#include "utilities.h"

// MIPS opcodes table
struct OPCODES_CONTENT opcodes_contents_table[] = {	/* 43 opcodes */
	{"add",		'R',	0x0,	0x20},
	{"addi",	'I',	0x8,	0x0},
	{"addiu",	'R',	0x0,	0x9},
	{"addu",	'R',	0x0,	0x21},
	{"and",		'R',	0x0,	0x24},
	{"andi",	'I',	0xc,	0x0},
	{"beq",		'I',	0x4,	0x0},
	{"blez",	'I',	0x6,	0x0},
	{"bne",		'I',	0x5,	0x0},
	{"bgtz",	'I',	0x7,	0x0},
	{"div",		'R',	0x0,	0x1a},
	{"divu",	'R',	0x0,	0x1b},
	{"j",		'J',	0x2,	0x0},
	{"jal",		'J',	0x3,	0x0},
	{"jr",		'R',	0x0,	0x8},
	{"lb",		'I',	0x20,	0x0},
	{"lbu",		'I',	0x24,	0x0},
	{"lhu",		'I',	0x25,	0x0},
	{"lui",		'R',	0x0,	0xf},
	{"lw",		'R',	0x0,	0x23},
	{"mfhi",	'R',	0x0,	0x10},
	{"mthi"	,	'R',	0x0,	0x11},
	{"mflo"	,	'R',	0x0,	0x12},
	{"mtlo"	,	'R',	0x0,	0x13},
	{"mfc0"	,	'R',	0x10,	0x0},
	{"mult"	,	'R',	0x0,	0x18},
	{"multu",	'R',	0x0,	0x19},
	{"nor",		'R',	0x0,	0x27},
	{"xor",		'R',	0x0,	0x26},
	{"or",		'R',	0x0,	0x25},
	{"ori",		'I',	0xd,	0x0},
	{"sb",		'I',	0x28,	0x0},
	{"sh",		'I',	0x29,	0x0},
	{"slt",		'R',	0x0,	0x2a},
	{"slti",	'I',	0xa,	0x0},
	{"sltiu",	'I',	0xb,	0x0},
	{"sltu",	'R',	0x0,	0x2b},
	{"sll",		'R',	0x0,	0x0},
	{"srl",		'R',	0x0,	0x2},
	{"sra",		'R',	0x0,	0x3},
	{"sub",		'R',	0x0,	0x22},
	{"subu",	'R',	0x0,	0x23},
	{"sw",		'I',	0x2b,	0x0}

};

//MIPS registers table
struct REGISTERS registers_table[] = {
	{"$zero",	0},
	{"$at", 	1},
	{"$v0", 	2},
	{"$v1", 	3},
	{"$a0", 	4},
	{"$a1", 	5},
	{"$a2", 	6},
	{"$a3", 	7},
	{"$t0", 	8},
	{"$t1", 	9},
	{"$t2", 	10},
	{"$t3", 	11},
	{"$t4", 	12},
	{"$t5", 	13},
	{"$t6", 	14},
	{"$t7", 	15},
	{"$s0", 	16},
	{"$s1", 	17},
	{"$s2", 	18},
	{"$s3", 	19},
	{"$s4", 	20},
	{"$s5", 	21},
	{"$s6", 	22},
	{"$s7", 	23},
	{"$t8", 	24},
	{"$t9", 	25},
	{"$k0", 	26},
	{"$k1", 	27},
	{"$gp", 	28},
	{"$fp", 	30},
	{"$ra", 	31},
};





char* get_text_section(unsigned char* heap_file, int file_length, int* text_section_size_ptr)
{
	//This function takes the text section in the MIPS ELF code end returns pointer to heap where the text, op codes are saved
	int i = 0, j = 0, founded = 0;
	unsigned int entrypoint = 0;
	uint32_t size = 0;
	void * code = NULL;
	unsigned char* text_section_alocated = NULL;
	void* fPointer = NULL;
	Elf32_Shdr* sh = NULL;
	Elf32_Shdr* text_section = NULL;
	Elf32_Ehdr* elfHeader = (Elf32_Ehdr*) heap_file;
	

	entrypoint = (elfHeader->e_entry);


	fPointer = heap_file + (elfHeader->e_shoff);
	
	
	for (i = 0; i < (elfHeader->e_shnum); i++)
	{
		fPointer += (elfHeader->e_shentsize);
		sh = (Elf32_Shdr*) fPointer;
	
		if (entrypoint >= (sh->sh_addr) && entrypoint < (sh->sh_addr) + (sh->sh_size))
		{
			text_section = sh; // pointer to the text section
			
			i = (elfHeader->e_shnum); // to stop the loop
			
			founded = 1;
		
		}
		
	}

	if (!founded)
	{
		printf("Problem in getting the text section! \n");

		return NULL; // if not found!
	}

	
	code = heap_file + (text_section->sh_offset);


	size = (text_section->sh_size);
	

	text_section_alocated = (char*) malloc(size);

	if (!text_section_alocated)
	{
		printf("problem allocating memory with malloc in get text section function! \n");
		return NULL;
	}

	
	memcpy(text_section_alocated, code, size);
	


	*text_section_size_ptr = size; // "returning" the size of the text section to the main file, in bits


	return text_section_alocated;
}



int sort_opcode_table(struct OPCODE* opcode_table, int opcode_table_size)
{
	int i = 0, j = 0, founded = 0, counter = 0, row = 0;


	for (i = 0; i < opcode_table_size; i++)
	{
		founded = 0;
		opcode_table[i].valid = 1;


		

		for (j = 0; j < OPCODE_CONTENTS_TABLE_SIZE; j++)
		{

			

			if ((opcodes_contents_table[j].opcode_hex == 0x0 || opcodes_contents_table[j].opcode_hex == 0x10) && (opcode_table[i].opcode_instruction_type.r_opcode.funct == opcodes_contents_table[j].funct) && founded == 0 && opcode_table[i].opcode_instruction_type.r_opcode.opcode == 0x0)
			{
				founded = 1;
					// if it's R OPCODE - nothing to do
				opcode_table[i].opcode_type = R_OPCODE;
			}
			

			if ((opcode_table[i].opcode_instruction_type.r_opcode.opcode == opcodes_contents_table[j].opcode_hex) && founded == 0 && (opcodes_contents_table[j].funct == 0))
			{
				if (opcodes_contents_table[j].type == 'I')
				{	// if the opcode is I OPCODE
				
					
					opcode_table[i].opcode_type = I_OPCODE;

					memcpy(&opcode_table[i].opcode_instruction_type.i_opcode, &opcode_table[i].opcode_instruction_type.r_opcode, SIZE_OF_OP_CODE / 8 /* 4 bytes */);

					founded = 1;
				}
				else if (opcodes_contents_table[j].type == 'J')
				{	// if the opcode is J OPCODE
					
					
					opcode_table[i].opcode_type = J_OPCODE;

					memcpy(&opcode_table[i].opcode_instruction_type.j_opcode, &opcode_table[i].opcode_instruction_type.r_opcode, SIZE_OF_OP_CODE / 8 /* 4 bytes */);

					founded = 1;
				}
			}

		}

		if (founded == 0) // if the opcode is not valid
		{
			opcode_table[i].valid = 0;
		}

			counter++;

			// saving the row of the opcode
			row++;

			opcode_table[i].row = row;
		


	}


	return 0;
}




int make_opcode_table(unsigned char* heap_file, int file_length, struct OPCODE* opcode_table, int opcode_table_size)
{	// This function makes a linked list of the op codes and saves them in the heap - returns the head of the linked list // can remove->->
	int i = 0, j = 0, k = 0, reverse = 0;
	union OPCODE_INSTRUCTION_TYPE* jumps = (union OPCODE_INSTRUCTION_TYPE*) heap_file;
	struct R_OPCODE temp = {0};
	
	for (i = 0; i < opcode_table_size; i++) // making the opcode table
	{
		

		memcpy(&opcode_table[i].opcode_instruction_type.r_opcode, jumps, SIZE_OF_OP_CODE / 8 /* 4 bytes */);
		
		
		jumps++;

	}

	if (sort_opcode_table(opcode_table, opcode_table_size) != 0) // sorting the opcodes for their types
	{
		printf("Problem in the sort opcode function! \n");
		return -1;
	}

	return 0;


}


int print_opcodes(struct OPCODE* opcode_table, int opcode_table_size)
{
	int i = 0, j = 0, k = 0, founded = 0;

	for (i = 0; i < opcode_table_size; i++)
	{
		founded = 0;

		
		if (opcode_table[i].valid == 1)
		{
			if (opcode_table[i].opcode_type == R_OPCODE)
			{	// if the opcode is R Type:
				
				//printf("opcode = %#x \n", opcode_table[i].opcode_instruction_type.r_opcode.opcode);
				for (j = 0; j < OPCODE_CONTENTS_TABLE_SIZE; j++)
				{
					if (opcode_table[i].opcode_instruction_type.r_opcode.funct == opcodes_contents_table[j].funct && opcodes_contents_table[j].type == 'R' && opcode_table[i].opcode_instruction_type.r_opcode.opcode == opcodes_contents_table[j].opcode_hex && founded == 0)
					{	
						founded = 1;

						// printing row
						printf("%d:    ", opcode_table[i].row);

						// printing the opcode
						printf("%s    ", opcodes_contents_table[j].opcode_name);

						// printing the rs register
						for (k = 0; k < REGISTERS_TABLE_SIZE; k++)
						{
							if (opcode_table[i].opcode_instruction_type.r_opcode.rs == registers_table[k].register_number)
							{
								printf("%s,", registers_table[k].register_name);
							}
						}

						// printing the rt register
						for (k = 0; k < REGISTERS_TABLE_SIZE; k++)
						{
							if (opcode_table[i].opcode_instruction_type.r_opcode.rt == registers_table[k].register_number)
							{
								printf("%s,", registers_table[k].register_name);
							}
						}

						// printing the rd register
						for (k = 0; k < REGISTERS_TABLE_SIZE; k++)
						{
							if (opcode_table[i].opcode_instruction_type.r_opcode.rd == registers_table[k].register_number)
							{
								printf("%s,", registers_table[k].register_name);
							}
						}


						printf("%#x\n", opcode_table[i].opcode_instruction_type.r_opcode.shift);

					}
				}
			}

			else if (opcode_table[i].opcode_type == I_OPCODE)
			{	// if the opcode is I Type:
				for (j = 0; j < OPCODE_CONTENTS_TABLE_SIZE; j++)
				{
					if (opcode_table[i].opcode_instruction_type.i_opcode.opcode == opcodes_contents_table[j].opcode_hex && opcodes_contents_table[j].type == 'I')
					{
						// printing row
						printf("%d:    ", opcode_table[i].row);

						// printing the opcode
						printf("%s    ", opcodes_contents_table[j].opcode_name);
						

						// printing the rs register
						for (k = 0; k < REGISTERS_TABLE_SIZE; k++)
						{
							if (opcode_table[i].opcode_instruction_type.i_opcode.rs == registers_table[k].register_number)
							{
								printf("%s,", registers_table[k].register_name);
							}
						}


						// printing the rt register
						for (k = 0; k < REGISTERS_TABLE_SIZE; k++)
						{
							if (opcode_table[i].opcode_instruction_type.i_opcode.rt == registers_table[k].register_number)
							{
								printf("%s,", registers_table[k].register_name);
							}
						}


						// printing the imm value (immediate)
						printf("%d\n", opcode_table[i].opcode_instruction_type.i_opcode.imm);
					}
				}
			}

			else
			{	// if the opcode is J Type:
				
				// printing row
				printf("%d:    ", opcode_table[i].row);

				for (j = 0; j < OPCODE_CONTENTS_TABLE_SIZE; j++)
				{
					// printing the opcode
					if (opcode_table[i].opcode_instruction_type.j_opcode.opcode == opcodes_contents_table[j].opcode_hex && opcodes_contents_table[j].type == 'J')
					{
						printf("%s    ", opcodes_contents_table[j].opcode_name);
					}
				}

				// printing the pseudo-address
				printf("%#x \n", opcode_table[i].opcode_instruction_type.j_opcode.address_to_jump);
			}
		}

		else
		{
			printf("%d:	Unrecognized opcode! \n", opcode_table[i].row);
		}
	}



	return 0;
}