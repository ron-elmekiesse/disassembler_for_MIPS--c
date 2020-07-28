
// This function gets the text section from the compiled mips file.
char* get_text_section(char* file_name, int file_length, int* text_section_size_ptr);


// This function makes an opcodes table , returns 0 if everything is okay.
int make_opcode_table(char* heap_file, int file_length, struct OPCODE* opcode_table, int opcode_table_size);


// This function sorts the opcodes as their types from the opcode table.
int sort_opcode_table(struct OPCODE* opcode_table, int opcode_table_size);


// This function prints out the full dissasemled instruction.
int print_opcodes(struct OPCODE* opcode_table, int opcode_table_size);