#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <stdint.h>
#include "sort_files_by_size.h"


#define SIZE_EXTENCION 10
#define NOPENFD 15

static int fn(const char *fpath, const struct stat *sb, int typeflag);
static int find_place_dict(long int size );
int str_put_in_dictionary(const char *fpath, long int size);



static struct dictionary dict;

/*
dict.fpaths = NULL;
dict.f_sizes = NULL;

dict.len_d = 0;
dict.size = 0;
*/

static int fn(const char *fpath, const struct stat *sb, int typeflag)
{
    int temp;
    long int size;
    if (typeflag == FTW_D) 
    {
        return 0;
    }
    size = (intmax_t) sb->st_size;
    temp = str_put_in_dictionary(fpath, size);
    
    if (temp == -1)
    {
        return -1;
    }
    return 0;
    
}

struct dictionary sort_files_by_size(const char *dir_name, int *error)
{
    
    dict.fpaths = NULL;
    dict.f_sizes = NULL;

    dict.len_d = 0;
    dict.size = 0;
    
    if(!(dir_name))
    {
        *error = -1;
        return dict;
    }
    
    if (ftw(dir_name, fn, NOPENFD) == -1) 
    {
        *error = -2;
        return dict;
	}
	
	dict.fpaths = realloc(dict.fpaths, ( dict.len_d )*sizeof(char*) );
    dict.f_sizes = realloc(dict.f_sizes, ( dict.len_d )*sizeof(char*) );
	
	*error = 0;
	return dict;
    
}



static int find_place_dict(long int size )
{
    int i = 0;
    for(i = 0; i < dict.len_d; i++)// finding place for fpath
    {
        if(dict.f_sizes[i]  < size)
            break;
    }
    return i;
}


int str_put_in_dictionary(const char *fpath, long int size)
{
    int place = 0; //place whhre to put fpath
    int len_w = strlen(fpath);
    
    if( dict.len_d >= dict.size ) //extendig size of dictionary
    {
        if( !(dict.fpaths = realloc(dict.fpaths, ( dict.size + SIZE_EXTENCION)*sizeof(char*) )) )
            return -1;
        
        if( !(dict.f_sizes = realloc(dict.f_sizes, ( dict.size + SIZE_EXTENCION)*sizeof(int*) )) )
            return -1;
        
        dict.size += SIZE_EXTENCION;
    }
    
    place = find_place_dict(size);
    
    for(int j = dict.len_d - 1 ; j >= place; j--)// puts dict.fpaths[dict.len_d] in correct position
    {
        dict.fpaths[j + 1] = dict.fpaths[j];
        dict.f_sizes[j + 1] = dict.f_sizes[j];
    }
    
    if( !(dict.fpaths[place] = (char*)malloc( (len_w + 1)*sizeof(char))) )
    {
        return -1;
    }
    
    
    strcpy(dict.fpaths[place], fpath);
    dict.f_sizes[place] = size;
    dict.len_d++;
    return 1;
}

