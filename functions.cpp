#include "functions.hpp"
#include "log.h"

void t_place_pointers (Strings *strings, Text * text)
{
    assert (text != NULL);
    assert (text->count_of_symbols != 0);

    int index_of_string = 1;
    int temp_index_of_symbol = 0;

    strings[0].string_number = text->my_text;

    for (int index_of_symbol = 0; index_of_symbol < text->count_of_symbols; index_of_symbol++)
    {   
        if (text->my_text[index_of_symbol] == '\0')
        {
            strings[index_of_symbol].string_len = index_of_symbol - temp_index_of_symbol;
            strings[index_of_string].string_number = text->my_text + index_of_symbol + 1;
            temp_index_of_symbol = index_of_symbol;
            index_of_string++;
        }  
    }

    text->my_text[text->count_of_symbols] = '\0';
}

void place_pointers (char ** string_number, Text * text)
{
    assert (string_number != NULL);
    assert (text != NULL);
    assert (text->count_of_symbols != 0);

    int index_of_string = 1;

    string_number[0] = text->my_text;

    for (int index_of_symbol = 0; index_of_symbol < text->count_of_symbols; index_of_symbol++)
    {   
        if (text->my_text[index_of_symbol] == '\0')
        {
            string_number[index_of_string] = text->my_text + index_of_symbol + 1;
            index_of_string++;
        }  
    }

    text->my_text[text->count_of_symbols] = '\0';
}

int count_and_read (FILE * input_file, Text * text)
{
    assert (input_file != NULL);
    assert (text != NULL);

    // struct stat buff;
    // fstat (fileno(input_file), &buff);
    // text->count_of_symbols = buff.st_size;                                 

    fseek(input_file, 0, SEEK_END);
    text->count_of_symbols = ftell(input_file)/sizeof(char);                                 

    fseek (input_file, 0, SEEK_SET);

    text->my_text = (char *) calloc ((text->count_of_symbols), sizeof (char));

    if (text->my_text == NULL)
        return NO_MEM_ERR;

    text->count_of_symbols = fread(text->my_text, sizeof(char), text->count_of_symbols, input_file);
    
    for (int index_of_symbol = 0; index_of_symbol < text->count_of_symbols; index_of_symbol++)
    {   
        if (text->my_text[index_of_symbol] == '\n')
        {
            text->my_text[index_of_symbol] = '\0';
            text->count_of_strings++; 
        }
    }
    text->count_of_strings++;
    
    fclose (input_file);
    
    return SUCCESS;
}

void write_to_file (char ** string_number, int count_of_strings, FILE * output_file)
{
    assert (string_number != NULL);
    assert (count_of_strings != 0);
    assert (output_file != NULL);

    for (int ind = 0; ind < count_of_strings; ind++)
    {
        char * temp = string_number[ind];
        
        while (*temp != '\0')
        {
            putc(*temp, output_file);
            temp++;
        }
        putc('\n', output_file);
    }
    
    putc('\n', output_file);
}

void print_origin (FILE * output_file, Text * text)
{
    for (int ind = 0; ind < text->count_of_symbols; ind++)
    {
        if (text->my_text[ind] == '\0')
            putc ('\n', output_file);
        else
            putc (text->my_text[ind], output_file);
    }
}

void sort (char ** string_number, int count_of_strings, int (* string_comparsion) (char *, char*))
{
    assert (string_number    != NULL);
    assert (count_of_strings != 0);

    for (int i = 0; i < count_of_strings; i++)
    {
        for (int j = 0; j < (count_of_strings - 1); j++)
        {
            if (string_comparsion (string_number[j], string_number[j + 1]))
            {
                swap(string_number, j);
            }
        }
    }
}


void swap(char **string_number, int j) 
{
    assert (string_number != NULL);

    char* temp = string_number[j];
                
    string_number[j] = string_number[j + 1];
    string_number[j + 1] = temp;
}


int string_comparsion (char * string1, char * string2)
{
    assert (string1 != NULL);
    assert (string2 != NULL);
 
    char * temp_string1 = string1;
    char * temp_string2 = string2;

    while (*temp_string1 != '\0' and *temp_string2 != '\0')
    {
        while (not_letter (*temp_string1) and *temp_string1 != '\0') 
            temp_string1++;
        while (not_letter (*temp_string2) and *temp_string2 != '\0')
            temp_string2++;
        
        if (*temp_string1 > *temp_string2)
            return RIGHT;
        else if (*temp_string1++ == *temp_string2++);
        else
            return LEFT;
        
        // temp_string1++;
        // temp_string2++;
    }
    if (*temp_string2 == '\0')
        return RIGHT;
    
    return EQUAL;
}


int reverse_string_comparsion (char * string1, char * string2)
{
    assert (string1 != NULL);
    assert (string2 != NULL);
    
    char * temp_string1 = string1;
    char * temp_string2 = string2;
    
    while (*temp_string1 != '\0' and *temp_string2 != '\0')
    {
        while (not_letter (*temp_string1) and *temp_string2 != '\0') 
            temp_string1--;
        while (not_letter (*temp_string2) and *temp_string2 != '\0')
            temp_string2--;
        
        if (*temp_string1 > *temp_string2)
            return RIGHT;

        if (*temp_string1 < *temp_string2)
            return LEFT;
        
        temp_string1--;
        temp_string2--;
    }
    if (*temp_string2 == '\0')
        return RIGHT;
    
    return EQUAL;
}



void reverse_strings (char ** string_number, Text *text, int direction)
{
    assert (string_number != NULL);
    assert (text->count_of_strings != 0);

    for (int i = 0; i < text->count_of_strings; i++)
    {
        while (*string_number[i] != '\0' and string_number[i] != text->my_text - 1)
            string_number[i] += direction;

        string_number[i] -= direction;
    }
}


bool not_letter (char symbol)
{
    if (('A' <= symbol and symbol <= 'Z') or ('a' <= symbol and symbol <= 'z'))
        return false;
    else
        return true;
}


bool check_param (int argc, char *first_arg, char *second_arg)
{

    if (argc == 1)
    {
        printf ("example: \\.prog input_file.txt output_file.txt\n");
        return FALL;
    }
    else if ((argc != 3))
    {
        printf ("incorrect number of parametrs \n\n" \
                "example: \\.prog input_file.txt output_file.txt\n\n");
        return FALL;
    }
    else if (strcmp(first_arg, second_arg) == 0)
    {
        printf ("names of input and output files are similar");
        
        return FALL;
    }
    else if (check_extension(first_arg, "txt") ==  ERROR or check_extension(second_arg, "txt") ==  ERROR)
    {
        printf ("files should have the .txt extension");
        return FALL;
    }
    return SUCCESS;
}


int check_extension (char *file_name, const char *extension)
{
    char *last_word = strchr(file_name, '.') + 1;

    if ((*last_word == 1) or (strcmp (last_word, extension) == 0))
        return SUCCESS;
    else
        return ERROR;
}


void quick_sort(char *string_number[], int low, int high, int (* string_comparsion) (char *, char *)) 
{
    if (low < high) 
    {
        int pi = partition(string_number, low, high, string_comparsion);

        quick_sort(string_number, low, pi - 1, string_comparsion);
        quick_sort(string_number, pi + 1, high, string_comparsion);
    }
}


int partition(char *string_number[], int low, int high, int (*string_comparsion) (char  *, char *))
{
    char * pivot = string_number[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) 
    {
        if (!string_comparsion (string_number[j], pivot)) 
        {
            i++;
        
            char* temp = string_number[j];
                        
            string_number[j] = string_number[i];
            string_number[i] = temp;
        }
    }

    char* temp = string_number[i + 1];
                        
    string_number[i + 1] = string_number[high];
    string_number[high] = temp;  

    return (i + 1);
}


void merge(char **string_number, int start, int midle, int stop)    
{    
    int i, j, k;  
    int n1 = midle - start + 1;    
    int n2 = stop - midle;    
      
    char * LeftArray[n1];
    char * RightArray[n2];
  
    for (int index = 0; index < n1; index++)    
        LeftArray[index] = string_number[start + index];    
    
    for (int index = 0; index < n2; index++)    
        RightArray[index] = string_number[midle + 1 + index];    
      
    i = 0;
    j = 0;
    k = start;
      
    while (i < n1 and j < n2)    
    {    
        if (string_comparsion(RightArray[j], LeftArray[i])) 
        {    
            string_number[k] = LeftArray[i];    
            i++;    
        }    
        else    
        {    
            string_number[k] = RightArray[j];    
            j++;    
        }    
        k++;    
    }    
    while (i < n1)    
    {    
        string_number[k] = LeftArray[i];    
        i++;    
        k++;    
    }    
      
    while (j < n2)    
    {    
        string_number[k] = RightArray[j];    
        j++;    
        k++;    
    }    
}    


void mergeSort(char ** string_number, int left, int right)
{
    if (left < right) 
    {
        int middle = left + (right - left) / 2;
  
        mergeSort(string_number, left, middle);
        mergeSort(string_number, middle + 1, right);
  
        merge(string_number, left, middle, right);
    }
}

int q_string_comparsion (const void * string1, const void * string2)
{
    assert (string1 != NULL);
    assert (string2 != NULL);

    const char * temp_string1 = *((const char **) string1);
    const char * temp_string2 = *((const char **) string2);

    while (*temp_string1 != '\0' and *temp_string2 != '\0')
    {
        while (not_letter (*temp_string1) and *temp_string1 != '\0') 
            temp_string1++;
        while (not_letter (*temp_string2) and *temp_string2 != '\0')
            temp_string2++;
        
        if (*temp_string1 > *temp_string2)
            return RIGHT;

        if (*temp_string1 < *temp_string2)
            return LEFT;
        
        temp_string1++;
        temp_string2++;
    }
    if (*temp_string2 == '\0')
        return RIGHT;
    
    return EQUAL;
}