#ifndef FUNCTIONS_HPP_INCLUDED
#define FUNCTIONS_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

enum DIRECTIONS
{
    LEFT = -1,
    EQUAL = 0,
    RIGHT = 1,
};

typedef struct
{
    char *my_text        = NULL; //< count roots of the quadratic equation
    signed int count_of_symbols = NAN; //< first root of the quadratic equation
    signed int count_of_strings = NAN; //< second root of the quadratic equation
} Text;

void sort (char** string_number, int count_of_strings, int (* string_comparsion) (char *, char*));
void sheker_sort(char **string_number, int count_of_string, int (* string_comparsion) (char *, char*));

void reverse_sort (char** string_number, Text * text);
void reverse_strings (char ** string_number, Text * text, int direction);
int string_comparsion(char * string1, char * string2);
int reverse_string_comparsion (char * string1, char * string2);
bool not_letter (char symbol);
void place_pointers (char ** string_number, Text * text);
void write_to_file (char ** string_number, const int count_of_strings, FILE * output_file);
void count_and_read (FILE * input_file, Text * Text);
int check_extension (char *file_name, const char *extension);
bool check_param (int argc, char *first_arg, char *second_arg);
void swap(char **string, int j);
void quick_sort(char *string_number[], int low, int high, int (* string_comparsion) (char *, char*));
int partition(char *string_number[], int low, int high, int (* string_comparsion) (char *, char*));
char * my_strcpy (char *destination, const char *source);

#endif // FUNCTIONS_INCLUDED