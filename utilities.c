#include "utilities.h"

char* reset_char_array(char* arr, int arr_length)
{
	int i = 0;

	for (i = 0 ; i < arr_length; i++)
	{
		arr[i] = '\0';
	}
	return arr;
}


int get_file_length(char* file_name)
{
	//This function return the length of the file with the null byte

	int length = 0;
	FILE* ptr = NULL;

	ptr = fopen(file_name, "rb");

	if (ptr == NULL)
	{
		printf("Error openning file %s! \n", file_name);
		exit(1);
	}

	fseek(ptr, 0, SEEK_END);

	length = ftell(ptr);

	fclose(ptr);

	return length;
}

char* read_file_to_heap(char* file_name, int length)
{
	// Thie function reads the inputed file to the heap memory

	char* ptr = NULL;
	FILE* file_ptr;

	file_ptr = fopen(file_name, "rb");

	ptr = (char*) malloc(length);

	fread(ptr, length, 1, file_ptr);

	fclose(file_ptr);

	return ptr;
}

int check_file_architecture(char* heap_file)
{
	short type = 0;

	type = *(short*)(heap_file + 0x12);

	if (type != 0x08) // MIPS type
	{
		return -1;
	}

	return 0;
}