#ifndef FUNCTIONS_HPP_INCLUDED
#define FUNCTIONS_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>

enum ERRORS_CODE 
{
    FALL            = 0,
    SUCCESS         = 1, 
    ERROR           = 2,
    INPUT_ERROR     = 3,
    OPEN_FILE_ERROR = 4,
    NO_MEM_ERROR    = 5, 
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

typedef struct
{
    char *string_number = NULL;
    int string_len = 0;
} Strings;

void reverse_strings           (Strings * strings, Text * text, int direction);
int  string_comparsion         (const void * string1, const void * string2);
int  reverse_string_comparsion (const void * string1, const void * string2);
bool not_letter                (char symbol);
void place_pointers            (Strings * strings, Text * text);
void write_to_file             (Strings * strings, const int count_of_strings, FILE * output_file);
int  check_extension           (char * file_name, const char * extension);
bool check_param               (int argc, char *first_arg, char * second_arg);
void my_quick_sort             (void * obj, size_t count_of_obj, size_t size_of_obj, int (*comparsion) (const void *, const void *));
void quick_sort                (char * strings, int low,  int high,  size_t size, int (*string_comparsion) (const void *, const void *));
int partition                  (char * strings, int low, int high, size_t size, int (*string_comparsion) (const void *, const void *));
void merge_sort                (Strings * strings, int left, int right, int (*string_comparsion) (const void *, const void *));
int  struct_comparsion         (const void * struct1, const void * struct2);
void print_origin              (Text * text, FILE * output_file);
ERRORS_CODE  count_and_read    (FILE * input_file, Text * Text);
void swap(char* a, char* b, size_t width);
#endif // FUNCTIONS_INCLUDED