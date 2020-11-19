#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "replace.h"
#include "../lib/exstring.h"

char *str_replace(char *string, const char *old, const char *replacement)
{
    int len_old = strlen(old), len_rep  = strlen(replacement), len = strlen(string);
    char *point, *result;
    int count = 0;
    int start_res, start_str;
    
    
    point = strstr(string, old);
    
    while(point)
    {
        int start = point - string;
        
        count ++;
        point = strstr(&string[start + len_old], old);
    }
        
    result = (char *)malloc( (len + count * (len_rep - len_old) + 1)*sizeof(char) );
    
    point = strstr(string, old);
    start_res = 0;
    start_str = 0;
    while(point)
    {
        int end = point - string;
        int num = end - start_str;
        
        strncpy(&result[start_res], &string[start_str], num );
        strcpy(&result[start_res + num], replacement);
        
        start_res = start_res + num + len_rep;
        start_str = start_str + num + len_old;
        point = strstr(&string[start_str], old);
    }
    
    if(start_str != len)
    {
        strcpy(&result[start_res], &string[start_str]);
    }
        
    result[len + count*(len_rep - len_old)] = '\0';

    return result;
}
