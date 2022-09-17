#include "functions.hpp"
#include "log.h"

void place_pointers (Strings *strings, Text * text)
{
    assert (strings != NULL);
    assert (text != NULL);

    int index_of_string = 1;

    int temp_index_of_symbol = 0;
    strings[0].string_number = text->my_text;
    for (int index_of_symbol = 0; index_of_symbol < text->count_of_symbols; index_of_symbol++)
    {   
        if (text->my_text[index_of_symbol] == '\0')
        {
            strings[index_of_string].string_len = index_of_symbol - temp_index_of_symbol;
            strings[index_of_string].string_number = text->my_text + index_of_symbol + 1;
            temp_index_of_symbol = index_of_symbol;
            index_of_string++;
        }
    }

    text->my_text[text->count_of_symbols] = '\0';
}

// void place_pointers (char ** string_number, Text * text)
// {
//     assert (string_number != NULL);
//     assert (text != NULL);
//     assert (text->count_of_symbols != 0);

//     int index_of_string = 1;

//     string_number[0] = text->my_text;

//     for (int index_of_symbol = 0; index_of_symbol < text->count_of_symbols; index_of_symbol++)
//     {   
//         if (text->my_text[index_of_symbol] == '\0')
//         {
//             string_number[index_of_string] = text->my_text + index_of_symbol + 1;
//             index_of_string++;
//         }  
//     }

//     text->my_text[text->count_of_symbols] = '\0';
// }


int count_and_read (FILE * input_file, Text * text)
{
    assert (input_file != NULL);
    assert (text != NULL);

    fseek(input_file, 0, SEEK_END);
    text->count_of_symbols = ftell(input_file);                                 

    fseek (input_file, 0, SEEK_SET);

    text->my_text = (char *) calloc ((text->count_of_symbols), sizeof (char));

    if (text->my_text == NULL)
        return NO_MEM_ERROR;
        
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


void write_to_file (Strings * strings, int count_of_strings, FILE * output_file)
{
    assert (strings != NULL);
    assert (count_of_strings != 0);
    assert (output_file != NULL);

    for (int i = 0; i < count_of_strings; i++)
    {
        char * temp = strings[i].string_number;
        
        while (*temp != '\0')
        {
            putc(*temp, output_file);
            temp++;
        }
        putc('\n', output_file);
    }
    
    putc('\n', output_file);
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

    char* temp_string1 = string1;
    char* temp_string2 = string2;

    while (*temp_string1 != '\0' and *temp_string2 != '\0')
    {

        while (not_letter (*temp_string1) and *temp_string2 != '\0') 
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
        else if (*temp_string1-- == *temp_string2--);
        else
            return EQUAL;
    }
    if (*temp_string2 == '\0')
        return RIGHT;
    
    return EQUAL;
}



void reverse_strings (Strings * strings, Text *text, int direction)
{
    assert (strings != NULL);
    assert (text != NULL);
    assert (text->count_of_strings != 0);

    for (int i = 0; i < text->count_of_strings; i++)
        strings[i].string_number += direction*strings[i].string_len;
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


void quick_sort(Strings *strings, int low, int high, int (* string_comparsion) (char *, char *)) 
{
    if (low < high) 
    {
        int pi = partition(strings, low, high, string_comparsion);

        quick_sort(strings, low, pi - 1, string_comparsion);
        quick_sort(strings, pi + 1, high, string_comparsion);
    }
}


int partition(Strings * strings, int low, int high, int (*string_comparsion) (char *, char *))
{
    char * pivot = strings[high].string_number;
    int i = (low - 1);
    for (int j = low; j < high; j++) 
    {
        if (string_comparsion (strings[j].string_number, pivot) != RIGHT) 
        {
            i++;
        
            char* temp = strings[j].string_number;
                        
            strings[j].string_number = strings[i].string_number;
            strings[i].string_number = temp;
        }
    }

    char* temp = strings[i + 1].string_number;
                        
    strings[i + 1].string_number = strings[high].string_number;
    strings[high].string_number = temp;  

    return (i + 1);
}


void merge(Strings * strings, int start, int middle, int stop, int (*string_comparsion) (char *, char *))    
{    
    int i, j, k;  
    int first_n = middle - start + 1;    
    int second_n = stop - middle;    
      
    char * left_array[first_n];
    char * right_array[second_n];
  
    for (i = 0; i < first_n; i++)    
        left_array[i] = strings[start + i].string_number;    
    
    for (j = 0; j < second_n; j++)    
        right_array[j] = strings[middle + 1 + j].string_number;    

    i = 0;
    j = 0;
    k = start;
      
    while (i < first_n and j < second_n)    
    {    
        if ((string_comparsion(left_array[i], right_array[j])) != RIGHT) 
        {    
            strings[k].string_number = left_array[i];    
            i++;  
        }    
        else    
        {    
            strings[k].string_number = right_array[j];    
            j++;    
        }    
        k++;    
    }    
    while (i < first_n)    
    {    
        strings[k].string_number = left_array[i];    
        i++;    
        k++;    
    }    
      
    while (j < second_n)    
    {    
        strings[k].string_number = right_array[j];    
        j++;    
        k++;    
    }    
}    

void merge_sort(Strings * strings, int left, int right, int (*string_comparsion) (char *, char *))
{
    if (left < right) 
    {
        int middle = left + (right - left) / 2;
  
        merge_sort(strings, left, middle, string_comparsion);
        merge_sort(strings, middle + 1, right, string_comparsion);
  
        merge(strings, left, middle, right, string_comparsion);
    }
}


int q_string_comparsion (const void * struct1, const void * struct2)
{
    assert (struct1 != NULL);
    assert (struct2 != NULL);

    const char* temp_string1 = ((const Strings *) struct1)->string_number;
    const char* temp_string2 = ((const Strings *) struct2)->string_number;

    while (*temp_string1 != '\0' and *temp_string2 != '\0')
    {

        while (not_letter (*temp_string1) and *temp_string2 != '\0') 
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


void print_origin (Text * text, FILE * output_file)
{
    assert (text != NULL);
    assert (output_file != NULL);

    for (int i = 0; i < text->count_of_symbols; i++)
    {       
        if (text->my_text[i] != '\0')
        {
            putc(text->my_text[i], output_file);
        }
        else
            putc('\n', output_file);
    }
    
    putc('\n', output_file);
}