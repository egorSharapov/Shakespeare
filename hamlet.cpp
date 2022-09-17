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


    if (count_and_read (input_file, &text) == NO_MEM_ERR)
        return FALL;
    
    //Strings strings[text.count_of_strings];
    //Strings *strings = (Strings *) calloc (text.count_of_strings, sizeof(Strings));


    char *string_number[text.count_of_strings];

    place_pointers (string_number, &text);

    //t_place_pointers (strings, &text);

    sort (string_number, text.count_of_strings, string_comparsion);
    //qsort (string_number, text.count_of_strings, sizeof (char *), q_string_comparsion);
    //quick_sort (string_number, 0, text.count_of_strings - 1, string_comparsion);
    //mergeSort (string_number, 0, text.count_of_strings);
    write_to_file (string_number, text.count_of_strings, output_file);
    
    
    reverse_strings (string_number, &text, RIGHT);
    //quick_sort (string_number, 0, text.count_of_strings - 1, reverse_string_comparsion);
    reverse_strings (string_number, &text, LEFT);
    
    write_to_file (string_number, text.count_of_strings, output_file);

    print_origin (output_file, &text);

    fclose(output_file);


    free(text.my_text);
   
    printf ("\nstrings: %d \nsymbols: %d",text.count_of_strings, text.count_of_symbols);
    
    return 0;
}