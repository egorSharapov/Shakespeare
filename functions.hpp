#ifndef FUNCTIONS_HPP_INCLUDED
#define FUNCTIONS_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


enum ERRORS_CODE 
{
    ERROR           = -1,
    FALL            = 0,
    SUCCESS         = 1, 
    INPUT_ERROR     = 3, ///< incorrect input error  
    OPEN_FILE_ERROR = 4, ///< error of open file
    COUNT_EQ_ERROR  = 5, ///< error count of eqations in input file
};


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
int check_extension (char *file_name, const char *extension);
bool check_param (int argc, char *first_arg, char *second_arg);
void swap(char **string, int j);

void quick_sort(char *string_number[], int low, int high);
int partition(char *string_number[], int low, int high);

#endif // FUNCTIONS_INCLUDED