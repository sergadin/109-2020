#include <stdio.h>
#include <stdlib.h>
#include "../lib/exstring.h"
#include "replace.h"

enum RETURN_CODES
{
    INPUT_ERROR = -3,
    MEMORY_ERROR,
    READ_ERROR,
};

int main(int argc, char **argv)
{
    char *name, *old_str, *replacement;
    FILE *file;
    
    if( (argc != 4) )
    {
        fprintf(stderr, "Usage: %s [name] [old string] [replacement string]\n", argv[0]);
        return INPUT_ERROR;
    }
    
    name = argv[1];
    old_str = argv[2];
    replacement  = argv[3]; 
    if( !(file = fopen(name, "r")) )
    {
        fprintf(stderr,"cant open file\n");
        return READ_ERROR;
    }
    
    
    while(!feof(file)) // proper cheak later dont worry
    {
        char *string;
        
        printf("////////////////line////////////////////\n");
        
        if( (( string = read_long_string(file) ) != NULL))
        {
            char *result;
            result = str_replace(string, old_str, replacement);
            printf("starting string\n%s\n", string );
            printf("resulting string\n%s\n", result );
            free(string);
            free(result);
        }
        else
        {
            if(!feof(file))
            {
                fprintf(stderr,"reading error\n");
                return READ_ERROR;
            }
        }
    }
    return 0;
}
