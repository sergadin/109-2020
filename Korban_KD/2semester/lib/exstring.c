#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "exstring.h"
#define num 1024

char *read_long_string(FILE *f)
{
    char buf[num], *result = NULL, *s;
    int len_s;
    int len_res = 0;
    
    s = fgets(buf, num, f);
    if(!s)
    {
        return NULL;
    }
    
    
    len_s = strlen(s);
    result  = (char *)malloc( (len_s + 1)*sizeof(char) );
    while(s)
    {
        if(s[len_s - 1] == '\n')
        {
            s[len_s - 1] = '\0';
            result = (char *)realloc(result, (len_res + len_s +1)*sizeof(char) );
            strcpy(&result[len_res], s);
            return result;
        }
        result = (char *)realloc(result, (len_res + len_s +1)*sizeof(char) );
        strcpy(&result[len_res], s);
        len_res += len_s;
        s = fgets(buf, num , f);
        
    }
    return result;
    
    
}
