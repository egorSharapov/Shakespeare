#ifndef FUNCTIONS_HPP_INCLUDED
#define FUNCTIONS_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void sort (char** string_number, int count_of_strings);
void reverse_sort (char** string_number, int count_of_strings, char * my_text);
void reverse_strings (char ** string_number, int count_of_strings);
void reverse_indexes (char ** string_number, int count_of_strings, char * my_text);
bool string_comparsion(char * string1, char * string2);
bool reverse_string_comparsion (char * string1, char * string2);
bool not_letter (char symbol);
void read_from_file (FILE * input_file, char ** string_number, int count_of_strings, char * my_text);
void write_to_file (char ** string_number, const int count_of_strings, FILE * output_file);
void count_symbols (FILE * input_file, int * count_of_symbols, int * count_of_strings);


#endif // FUNCTIONS_INCLUDED