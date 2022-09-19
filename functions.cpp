#include "functions.hpp"
#include "log.h"

void place_pointers (Strings *strings, Text * text)
{
    assert (strings != NULL);
    assert (text    != NULL);

    int index_of_string = 0;
    
    strings[0].string_number = text->my_text;
    
    for (int index_of_symbol = 0; index_of_symbol < text->count_of_symbols; index_of_symbol++)
    {   
        if (text->my_text[index_of_symbol] == '\0')
        {
            strings[index_of_string + 1].string_number = text->my_text + index_of_symbol + 1;
            strings[index_of_string].string_len = strlen (strings[index_of_string].string_number);
            
            index_of_string++;
        }
    }
    strings[index_of_string].string_len = strlen (strings[index_of_string].string_number);
    //printf ("%s  %d\n", strings[index_of_string].string_number, strings[index_of_string].string_len);
}


ERRORS_CODE count_and_read (FILE *input_file, Text * text)
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
    text->my_text[text->count_of_symbols] = '\0';

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
    assert (strings          != NULL);
    assert (count_of_strings != 0);
    assert (output_file      != NULL);

    for (int index = 0; index < count_of_strings; index++)
    {
        fwrite (strings[index].string_number, sizeof(char), strings[index].string_len, output_file);
        putc('\n', output_file);
    }
    
    putc('\n', output_file);
}


int string_comparsion (const void * string1, const void * string2)
{
    assert (string1 != NULL);
    assert (string2 != NULL);

    const char* temp_string1 = (const char *) string1;
    const char* temp_string2 = (const char *) string2;

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


int reverse_string_comparsion (const void * string1, const void * string2)
{
    assert (string1 != NULL);
    assert (string2 != NULL);

    const char* temp_string1 = (const char *) string1;
    const char* temp_string2 = (const char *) string2;

    while (*temp_string1 != '\0' and *temp_string2 != '\0')
    {

        while (not_letter (*temp_string1) and *temp_string1 != '\0') 
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



void reverse_strings (Strings * strings, Text *text, int direction)
{
    assert (strings != NULL);
    assert (text    != NULL);
    assert (text->count_of_strings != 0);

    for (int i = 0; i < text->count_of_strings; i++)
        strings[i].string_number += direction*(strings[i].string_len - 1);

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
    else if (check_extension(first_arg,  "txt") ==  ERROR or 
             check_extension(second_arg, "txt") ==  ERROR)
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


void my_quick_sort (void * obj, size_t count_of_obj, size_t size_of_obj, int (*comparsion) (const void *, const void *))
{
    char * points = (char *) obj;
    quick_sort (points, 0, count_of_obj - 1, size_of_obj, comparsion);
}


void quick_sort (char *strings, int low, int high, size_t size, int (* comparsion) (const void *, const void *)) 
{
    if (low < high) 
    {
        int pi = partition(strings, low, high, size, comparsion);

        quick_sort(strings, low, pi - 1, size, comparsion);
        quick_sort(strings, pi + 1, high, size, comparsion);
    }
}


int partition (char * strings, int low, int high, size_t size, int (*comparsion) (const void *, const void *))
{
    char * pivot = (strings + high*size);
    int i = (low - 1);
    for (int j = low; j < high; j++) 
    {
        if (comparsion ((strings + j*size), pivot) != RIGHT) 
        {
            i++;

            swap (strings + j*size, strings + i*size, size);
        }
    }

    swap (strings + (i + 1)*size, strings + high*size, size);

    return (i + 1);
}


static void merge (Strings * strings, int start, int middle, int stop, int (*string_comparsion) (const void *, const void *))    
{    
    int i, j, k;  
    int first_n = middle - start + 1;    
    int second_n = stop - middle;    
      
    Strings left_array[first_n];
    Strings right_array[second_n];
  
    for (i = 0; i < first_n; i++)    
        left_array[i] = strings[start + i];    
    
    for (j = 0; j < second_n; j++)    
        right_array[j] = strings[middle + 1 + j];    

    i = 0;
    j = 0;
    k = start;
      
    while (i < first_n and j < second_n)    
    {    
        if ((string_comparsion(left_array[i].string_number, right_array[j].string_number)) != RIGHT) 
        {    
            strings[k] = left_array[i];    
            i++;  
        }    
        else    
        {    
            strings[k] = right_array[j];    
            j++;    
        }    
        k++;    
    }    
    while (i < first_n)    
    {    
        strings[k] = left_array[i];    
        i++;    
        k++;    
    }    
      
    while (j < second_n)    
    {    
        strings[k] = right_array[j];    
        j++;    
        k++;    
    }    
}    


void merge_sort (Strings * strings, int left, int right, int (*string_comparsion) (const void *, const void *))
{
    if (left < right) 
    {
        int middle = left + (right - left) / 2;
  
        merge_sort(strings, left, middle, string_comparsion);
        merge_sort(strings, middle + 1, right, string_comparsion);
  
        merge(strings, left, middle, right, string_comparsion);
    }
}


int struct_comparsion (const void * struct1, const void * struct2)
{
    assert (struct1 != NULL);
    assert (struct2 != NULL);

    char* temp_string1 = ((const Strings *) struct1)->string_number;
    char* temp_string2 = ((const Strings *) struct2)->string_number;

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


void print_origin (Text * text, FILE * output_file)
{
    assert (text != NULL);
    assert (output_file != NULL);

    char * point = text->my_text;

    for (int i = 0; i < text->count_of_strings; i++)
        point += fprintf (output_file, "%s\n", point);

}


void swap(char* obj1, char* obj2, size_t width)
{
    while (width--)
    {
        char const temp = *obj1;
        *obj1++ = *obj2;
        *obj2++ = temp;
    }
}
