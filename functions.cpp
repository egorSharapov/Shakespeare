#include "functions.hpp"
#include "log.h"

void place_pointers (char ** string_number, Text * text)
{
    assert (string_number != NULL);
    assert (text != NULL);
    assert (text->count_of_symbols != 0);

    int index_of_string = 1;

    string_number[0] = text->my_text;

    for (int index_of_symbol = 0; index_of_symbol < text->count_of_symbols; index_of_symbol++)
    {   
        if (text->my_text[index_of_symbol] == '\n')
        {
            string_number[index_of_string] = text->my_text + index_of_symbol + 1;
            index_of_string++;
        }  
    }

    text->my_text[text->count_of_symbols] = '\n';
}


void count_and_read (FILE * input_file, Text * text)
{
    assert (input_file != NULL);
    assert (text != NULL);

    fseek(input_file, 0, SEEK_END);
    text->count_of_symbols = ftell(input_file)/sizeof(char);                                 

    fseek (input_file, 0, SEEK_SET);

    text->my_text = (char *) calloc ((text->count_of_symbols), sizeof (char));
        
    text->count_of_symbols = fread(text->my_text, sizeof(char), text->count_of_symbols, input_file);
    
    for (int index_of_symbol = 0; index_of_symbol < text->count_of_symbols; index_of_symbol++)
    {   
        if (text->my_text[index_of_symbol] == '\n')
            text->count_of_strings++; 
    }
    text->count_of_strings++;
    
    fclose (input_file);
}


void write_to_file (char ** string_number, int count_of_strings, FILE * output_file)
{
    assert (string_number != NULL);
    assert (count_of_strings != 0);
    assert (output_file != NULL);

    for (int i = 0; i < count_of_strings; i++)
    {
        char * temp = string_number[i];
        
        while (*temp != '\n')
        {
            putc(*temp, output_file);
            temp++;
        }
        putc(*temp, output_file);
    }
    
    putc('\n', output_file);
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

    while (*temp_string1 != '\n' and *temp_string2 != '\n')
    {
        while (not_letter (*temp_string1) and *temp_string2 != '\n') 
            temp_string1++;
        while (not_letter (*temp_string2) and *temp_string2 != '\n')
            temp_string2++;
        
        if (*temp_string1 > *temp_string2)
            return RIGHT;
        else if (*temp_string1++ == *temp_string2++);

        else
            return EQUAL;
    }
    if (*temp_string2 == '\n')
        return RIGHT;
    
    return EQUAL;
}


int reverse_string_comparsion (char * string1, char * string2)
{
    assert (string1 != NULL);
    assert (string2 != NULL);
    
    char * temp_string1 = string1;
    char * temp_string2 = string2;
    
    while (*temp_string1 != '\n' and *temp_string2 != '\n')
    {
        while (not_letter (*temp_string1) and *temp_string2 != '\n') 
            temp_string1--;
        while (not_letter (*temp_string2) and *temp_string2 != '\n')
            temp_string2--;
        

        if (*temp_string1 > *temp_string2)
            return RIGHT;
        else if (*temp_string1-- == *temp_string2--);
        else
            return EQUAL;
    }
    if (*temp_string2 == '\n')
        return RIGHT;
    
    return EQUAL;
}



void reverse_strings (char ** string_number, Text *text, int direction)
{
    assert (string_number != NULL);
    assert (text->count_of_strings != 0);

    for (int i = 0; i < text->count_of_strings; i++)
    {
        while (*string_number[i] != '\n' and string_number[i] != text->my_text - 1)
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


int partition(char *string_number[], int low, int high, int (*string_comparsion) (char *, char *))
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


void sheker_sort(char **string_number, int count_of_string, int (* string_comparsion) (char *, char *))
{
    int left = 0, right = count_of_string - 1;
    bool flag = true;
    
    while ((left < right) and flag)
    {
        flag = false;
        for (int i = left; i < right; i++)
        {
            if (string_comparsion(string_number[i], string_number[i + 1])) 
            {
                swap (string_number, i);
                flag = true;
            }
        }
        right--;
        
        for (int i = right; i > left; i--)
        {
            if (string_comparsion (string_number[i - 1], string_number[i]))
            {
                swap (string_number, i);
                flag = true;
            }
        }
        
        left++;
    }
}
