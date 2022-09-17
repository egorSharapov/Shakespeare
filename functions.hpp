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
    NO_MEM_ERROR  = 5, 
};


enum DIRECTIONS
{
    LEFT = -1,
    EQUAL = 0,
    RIGHT = 1,
};


typedef struct
{
    char *my_text        = NULL;
    int count_of_symbols = 0;
    int count_of_strings = 0;
} Text;

struct Strings
{
    char * string_number = NULL;
    int string_len = 0;
};

void reverse_strings (Strings * strings, Text * text, int direction);
int  string_comparsion (char * string1, char * string2);
int  reverse_string_comparsion (char * string1, char * string2);
bool not_letter (char symbol);
void place_pointers (Strings *strings, Text * text);
void write_to_file (Strings * strings, const int count_of_strings, FILE * output_file);
int  count_and_read (FILE * input_file, Text * Text);
int  check_extension (char *file_name, const char *extension);
bool check_param (int argc, char *first_arg, char *second_arg);
void swap           (char **string, int j);
void quick_sort(Strings * strings, int low, int high, int (* string_comparsion) (char *, char *));
int partition(Strings *strings, int low, int high, int (* string_comparsion) (char *, char *));
void merge(Strings * strings, int start, int midle, int stop, int (*string_comparsion) (char *, char *));
void merge_sort(Strings * strings, int left, int right, int (*string_comparsion) (char *, char *));
int q_string_comparsion (const void * struct1, const void * struct2);
void print_origin (Text *text, FILE * output_file);
#endif // FUNCTIONS_INCLUDED