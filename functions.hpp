#ifndef FUNCTIONS_HPP_INCLUDED
#define FUNCTIONS_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <sys\stat.h>
#include <sys\types.h>
#include <fcntl.h>
#include <unistd.h>

enum ERRORS_CODE 
{
    ERROR           = 2,
    FALL            = -1,
    SUCCESS         = 1, 
    INPUT_ERROR     = 3, ///< incorrect input error  
    OPEN_FILE_ERROR = 4, ///< error of open file
    NO_MEM_ERR      = 5,
};


enum DIRECTIONS
{
    LEFT = -1,
    EQUAL = 0,
    RIGHT = 1,
};


typedef struct
{
    char *my_text               = NULL;
    signed int count_of_symbols = 0;
    signed int count_of_strings = 0;
} Text;


typedef struct
{
    char * string_number  = NULL;
    unsigned string_len = 0;
} Strings;

void sort (char** string_number, int count_of_strings, int (* string_comparsion) (char *, char*));
void sheker_sort(char **string_number, int count_of_string, int (* string_comparsion) (char *, char*));
void reverse_strings (char ** string_number, Text * text, int direction);
int string_comparsion(char * string1, char * string2);
int reverse_string_comparsion (char * string1, char * string2);
bool not_letter (char symbol);
void place_pointers (char ** string_number, Text * text);
void write_to_file (char ** string_number, const int count_of_strings, FILE * output_file);
int count_and_read (FILE * input_file, Text * Text);
int check_extension (char *file_name, const char *extension);
bool check_param (int argc, char *first_arg, char *second_arg);
void swap(char **string, int j);
void quick_sort(char *string_number[], int low, int high, int (* string_comparsion) (char *, char*));
int partition(char *string_number[], int low, int high, int (* string_comparsion) (char *, char *));
void print_origin (FILE * output_file, Text * text);
int q_string_comparsion (const void * string1, const void * string2);

void t_place_pointers (Strings *strings, Text * text);
void merge(char **string_number, int start, int midle, int stop);
void mergeSort(char ** string_number, int left, int right);

#endif // FUNCTIONS_INCLUDED