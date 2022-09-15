#include "functions.hpp"


void read_from_file (FILE * input_file, char ** string_number, const int count_of_symbols, char * my_text)
{
    assert (input_file != NULL);
    assert (string_number != NULL);
    assert (my_text != NULL);

    char symbol = '\n';
    int index_of_string = 1;

    string_number[0] = my_text;
    
    for (int index_of_symbol = 0; index_of_symbol < count_of_symbols; index_of_symbol++)
    {   
        symbol = (char) fgetc (input_file);
        my_text[index_of_symbol] = symbol;

        if (symbol == '\n')
        {
            string_number[index_of_string] = my_text + index_of_symbol + 1;
            index_of_string++;
        }  
    }
    my_text[count_of_symbols] = '\n';


}


void count_symbols (FILE * input_file, int * count_of_symbols, int * count_of_strings)
{
    assert (input_file != NULL);
    assert (count_of_strings != 0);
    assert (count_of_symbols != 0);
    
    char symbol = '\n';
    (*count_of_strings)++;

    while (true)
    {
        symbol = (char) fgetc(input_file);
        if (symbol == EOF) break;
        if (symbol == '\n') (*count_of_strings)++;
        (*count_of_symbols)++;
    }
    
    fseek (input_file, 0, SEEK_SET);
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


void sort (char ** string_number, int count_of_strings)
{
    assert (string_number != NULL);
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
    char* temp = string_number[j];
                
    string_number[j] = string_number[j + 1];
    string_number[j + 1] = temp;
}


bool string_comparsion (char * string1, char * string2)
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
            return true;
        else if (*temp_string1++ == *temp_string2++);

        else
            return false;
    }

    if (*temp_string2 == '\n')
        return true;
    
    return false;
}


void reverse_sort (char ** string_number, int count_of_strings, char * my_text)
{
    assert (string_number != NULL);
    assert (count_of_strings != 0);
    assert (my_text != NULL);

    reverse_strings (string_number, count_of_strings);
    
    for (int i = 0; i < count_of_strings; i++)
    {
        for (int j = 0; j < (count_of_strings - 1); j++)
        {
            if (reverse_string_comparsion (string_number[j], string_number[j + 1]))
            {
                char* temp = string_number[j];
                
                string_number[j] = string_number[j + 1];
                string_number[j + 1] = temp;
            }
        }
    }
    reverse_indexes (string_number, count_of_strings, my_text);
}


bool reverse_string_comparsion (char * string1, char * string2)
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
            return true;
        else if (*temp_string1-- == *temp_string2--);
        else
            return false;
    }
    if (*temp_string2 == '\n')
        return true;
    
    return false;
}



void reverse_strings (char ** string_number, int count_of_strings)
{
    assert (string_number != NULL);
    assert (count_of_strings != 0);

    for (int i = 0; i < count_of_strings; i++)
    {
        while (*string_number[i] != '\n')
            string_number[i]++;

        string_number[i]--;
    }
}


void reverse_indexes (char ** string_number, int count_of_strings, char * my_text)
{
    assert (string_number != NULL);
    assert (count_of_strings != 0);
    assert (my_text != NULL);

    for (int i = 0; i < count_of_strings; i++)
    {
        while (*string_number[i] != '\n' and string_number[i] != my_text - 1)
        {
            string_number[i]--;
        }
        string_number[i]++;
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
    // else if (*first_arg == *second_arg)
    // {
    //     printf ("names of input and output files are similar");
    //     return FALL;
    // }
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

    if (strcmp (last_word, extension) == 0)
        return SUCCESS;
    else
        return ERROR;
}


int partition(char *string_number[], int low, int high)
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

void quick_sort(char *string_number[], int low, int high) 
{
    if (low < high) 
    {
        int pi = partition(string_number, low, high);

        quick_sort(string_number, low, pi - 1);
        quick_sort(string_number, pi + 1, high);
    }
}
