#include "functions.hpp"

const char *input_name = "Hamlet_input.txt";
const char *output_name = "Hamlet_output.txt";

int main (int argc, char *argv[])
{
    FILE *input_file;
    FILE *output_file;
    
    if (!check_param (argc, argv[1], argv[2])) 
        return INPUT_ERROR;

    if (!(input_file = fopen (argv[1], "r")) or !(output_file = fopen (argv[2], "w")))
        return FALL;

    char * my_text = NULL;
    int count_of_symbols = 0;
    int count_of_strings = 0;

    count_symbols (input_file, &count_of_symbols, &count_of_strings);

    my_text = (char *) calloc ((count_of_symbols + 1), sizeof (char));

    char *string_number[count_of_strings];
    char *temp_string_number[count_of_strings];

    read_from_file (input_file, string_number, count_of_symbols, my_text);
    fclose(input_file);

    for (int i = 0; i < count_of_strings; i++)
        temp_string_number[i] = string_number[i];
    
    //sort (string_number, count_of_strings);   
    quick_sort (string_number, 0, count_of_strings - 1);
    write_to_file (string_number, count_of_strings, output_file);
    
    reverse_sort (string_number, count_of_strings, my_text);
    //reverse_quick_sort (string_number, count_of_strings, my_text);
    write_to_file (string_number, count_of_strings, output_file);

    write_to_file (temp_string_number, count_of_strings, output_file);
    fclose(output_file);

    free(my_text);
    
    printf ("\nstrings: %d \nsymbols: %d",count_of_strings, count_of_symbols);
    
    return 0;
}