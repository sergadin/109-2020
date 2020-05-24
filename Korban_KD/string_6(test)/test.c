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
    struct dictionary dict;
    int  error;
    int i = 0;
    
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
    
    if(!dict.words)
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
    
    while( strlen(dict.words[i])  != 0)
    {
        printf("%s\n", dict.words[i]);
        free(dict.words[i]);
        i++;
    }
    free(dict.words[i]);
    

    free(dict.words);
    

    return 0;
}
