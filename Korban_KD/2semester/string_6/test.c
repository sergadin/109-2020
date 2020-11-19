#include <stdio.h>
#include <stdlib.h>
#include "sort_words_file.h"
#include <string.h>

enum RETURN_CODES
{
    INPUT_ERROR = -3,
    MEMORY_ERROR,
    READ_ERROR,
};

int main(int argc, char **argv)
{
    FILE *file;
    char *name;
    char **dictionary;
    int  error;
    int i = 0;
    
    if( (argc != 2) )
    {
        fprintf(stderr, "Usage: %s [name]\n", argv[0]);
        return INPUT_ERROR;
    }
    
    name = argv[1];
    
    if( !(file = fopen(name, "r")) )
    {
        fprintf(stderr, "ERROR can't open %s\n", name);
        return INPUT_ERROR;
    }
    
    dictionary = sort_words_file(file, &error);
    
    if(!dictionary)
    {
        switch(error)
        {
            case 2:
                fprintf(stderr, "ERROR can't read element from %s\n", name);
                return READ_ERROR;
            case 3:
                fprintf(stderr, "Memory ERROR!\n");
                return MEMORY_ERROR;
        }
    }
    
    while( strlen(dictionary[i])  != 0)
    {
        printf("%s\n", dictionary[i]);
        free(dictionary[i]);
        i++;
    }
    free(dictionary[i]);
    
    //i++;
    //printf("%s\n", dictionary[1]);
    free(dictionary);
    

    return 0;
}
