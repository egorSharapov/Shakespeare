#include "functions.hpp"
#include "log.h"

int main (int argc, char *argv[])
{

    FILE *input_file = NULL;
    FILE *output_file = NULL;

    Text text = {};
    if (!check_param (argc, argv[1], argv[2])) 
        return INPUT_ERROR;

    if (!(input_file = fopen (argv[1], "r")) or !(output_file = fopen (argv[2], "w")))
        return FALL;

    if (count_and_read (input_file, &text) == NO_MEM_ERROR)
        return NO_MEM_ERROR;
    
    Strings *strings = (Strings *) calloc (text.count_of_strings, sizeof (Strings));

    place_pointers (strings, &text);

    qsort (strings, text.count_of_strings, sizeof (Strings *), q_string_comparsion);
    merge_sort (strings, 0, text.count_of_strings - 1, string_comparsion);
    //quick_sort (strings, 0, text.count_of_strings - 1, string_comparsion);
    write_to_file (strings, text.count_of_strings, output_file);
    
    
    reverse_strings (strings, &text, RIGHT);
    quick_sort (strings, 0, text.count_of_strings - 1, reverse_string_comparsion);
    reverse_strings (strings, &text, LEFT);

    print_origin (&text, output_file);
    fclose(output_file);

    free(text.my_text);
   
    printf ("\nstrings: %d \nsymbols: %d",text.count_of_strings, text.count_of_symbols);
    
    return 0;
}