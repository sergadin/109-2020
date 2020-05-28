#include <stdio.h>
#include <stdlib.h>
#include "sort_files_by_size.h"
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
    char *name, *dir_name;
    struct dictionary dict;
    int  error;
    
    if( (argc != 3) )
    {
        fprintf(stderr, "Usage: %s [directories name] [name of output file]\n", argv[0]);
        return INPUT_ERROR;
    }
    
    name = argv[2];
    dir_name = argv[1];
    
    if( !(file = fopen(name, "w")) )
    {
        fprintf(stderr, "ERROR can't open %s\n", name);
        return INPUT_ERROR;
    }
    
    dict = sort_files_by_size(dir_name, &error);
    if(error != 0)
    {
        for(int i = 0; i < dict.len_d; i++)
        {
            fprintf(file, "size in bytes:%ld %s\n", dict.f_sizes[i], dict.fpaths[i]);
            printf("size in bytes: %ld %s\n", dict.f_sizes[i], dict.fpaths[i]);
            free(dict.fpaths[i]);
        }
        switch(error)
        {
            case -1:
                fprintf(stderr, "directories name is empty\n");
                return -5;
            case -2:
                fprintf(stderr, "Memory ERROR!\n");
                return MEMORY_ERROR;
        }
    }
    
    for(int i = 0; i < dict.len_d; i++)
    {
        fprintf(file, "size in bytes:%ld %s\n", dict.f_sizes[i], dict.fpaths[i]);
        printf("size in bytes: %ld %s\n", dict.f_sizes[i], dict.fpaths[i]);
        free(dict.fpaths[i]);
    }
    
    free(dict.f_sizes);
    free(dict.fpaths);
    

    return 0;
}
