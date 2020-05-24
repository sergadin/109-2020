#include <stdio.h>
#include <stdlib.h>
#include "sort_words_file.h"
#include <string.h>

int main(int argc, char **argv)
{
    FILE *file;
    char *name;
    struct dictionary dict;
    int  error;
    
    if( (argc != 2) )
    {
        fprintf(stderr, "Usage: %s [name of file]\n", argv[0]);
        return INPUT_ERROR;
    }
    
    name = argv[1];
    
    if( !(file = fopen(name, "r")) )
    {
        fprintf(stderr, "ERROR can't open %s\n", name);
        return INPUT_ERROR;
    }
    
    dict = sort_words_file(file, &error);
    
    if(error != 0)
    {
        switch(error)
        {
            case INPUT_ERROR:
                fprintf(stderr, "file: %s is empty\n", name);
                return INPUT_ERROR;
            case READ_ERROR:
                fprintf(stderr, "ERROR can't read element from %s\n", name);
                return READ_ERROR;
            case MEMORY_ERROR:
                fprintf(stderr, "Memory ERROR!\n");
                return MEMORY_ERROR;
        }
    }
    
    for(int i = 0; i < dict.len_d; i++)
    {
        printf("%s\n", dict.words[i]);
        free(dict.words[i]);
    }
    

    free(dict.words);
    

    return 0;
}
