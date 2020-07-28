#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <linux/types.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>


#define NAME_SIZE 20

#define SIZE_OF_OP_CODE 32 // without the null byte

#define MAX_OPCODE_NAME 5 // without the null byte

#define OPCODE_CONTENTS_TABLE_SIZE sizeof(opcodes_contents_table) / sizeof(struct OPCODES_CONTENT)

#define REGISTER_NAME_SIZE 5

#define REGISTERS_TABLE_SIZE sizeof(registers_table) / sizeof(struct REGISTERS)

#define REVERSE16(num) ((num>>8) | (num<<8))

#define REVERSE32(num) (((num>>24)&0xff) | ((num<<8)&0xff0000) |  ((num>>8)&0xff00) | ((num<<24)&0xff000000))


struct R_OPCODE // 32 bits size in total
{
	unsigned int opcode : 6;
	unsigned int rs 	: 5;
	unsigned int rt 	: 5;
	unsigned int rd 	: 5;
	unsigned int shift 	: 5;
	unsigned int funct 	: 6;
};


struct I_OPCODE // 32 bits size in total
{
	unsigned int opcode : 6;
	unsigned int rs 	: 5;
	unsigned int rt 	: 5;
	unsigned int imm 	: 16;
};


struct J_OPCODE // 32 bits size in total
{
	unsigned int opcode 		 : 6;
	unsigned int address_to_jump  : 26;
};

enum OPCODE_TYPE
{
	R_OPCODE  = 0,
	I_OPCODE = 1,
	J_OPCODE = 2
};

union OPCODE_INSTRUCTION_TYPE
{
	struct R_OPCODE r_opcode;
	struct I_OPCODE i_opcode;	// all the structs are 32 bits size
	struct J_OPCODE j_opcode;
};


struct OPCODE
{
	
	int row;
	union OPCODE_INSTRUCTION_TYPE opcode_instruction_type;
	enum OPCODE_TYPE opcode_type;
	int valid;

};

struct OPCODES_CONTENT
{
	char opcode_name[MAX_OPCODE_NAME];
	char type;
	int opcode_hex;
	int funct;
};

struct REGISTERS
{
	char register_name[REGISTER_NAME_SIZE];
	int register_number;
};


// This function resets char array given.
char* reset_char_array(char* arr, int arr_length);

// This function return the length of the file with the null byte.
int get_file_length(char* file_name);

// This function reads the inputed file to the heap memory.
char* read_file_to_heap(char* file_name, int length);

// This function check if the file given is for MIPS architecture.
int check_file_architecture(char* heap_file);