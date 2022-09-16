#include "functions.hpp"
#include "log.h"

const char *input_name = "Hamlet_input.txt";
const char *output_name = "Hamlet_output.txt";

int main (int argc, char *argv[])
{
    FILE *input_file = NULL;
    FILE *output_file = NULL;
    
    Text text = {};
    
    if (!check_param (argc, argv[1], argv[2])) 
        return INPUT_ERROR;

    if (!(input_file = fopen (argv[1], "r")) or !(output_file = fopen (argv[2], "w")))
        return FALL;


    count_symbols (input_file, &text);

    char *string_number[text.count_of_strings];
    char *temp_string_number[text.count_of_strings] ;

    read_from_file (input_file, string_number, &text);

    for (int i = 0; i < text.count_of_strings; i++)
        temp_string_number[i] = string_number[i];
    
    //sort (string_number, text.count_of_strings);
    //qsort (string_number, text.count_of_strings, sizeof (char *), string_comparsion);
    quick_sort (string_number, 0, text.count_of_strings - 1);
    write_to_file (string_number, text.count_of_strings, output_file);
    
    // reverse_sort (string_number, &text);
    reverse_strings (string_number, text.count_of_strings);
    reverse_quick_sort (string_number, 0, text.count_of_strings - 1);
    reverse_indexes (string_number, &text);
    
    write_to_file (string_number, text.count_of_strings, output_file);

    write_to_file (temp_string_number, text.count_of_strings, output_file);
    fclose(output_file);

    free(text.my_text);
   
    printf ("\nstrings: %d \nsymbols: %d",text.count_of_strings, text.count_of_symbols);
    
    return 0;
}