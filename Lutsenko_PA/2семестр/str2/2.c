#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "2.h"

char *read_long_string(FILE *f)
{
    char buf[1024];
    buf[0] = 0;
  
    char *s = fgets(buf, 1024, f);
    if(s) {
        unsigned long len = strlen(s);
        char *result = malloc(len + 1);
        strcpy(result, s);
        return result;
    }
    return NULL;
}

void replace(const char *s, const char *oldW,const char *newW)
{
    char *result;
    int i, cnt = 0;
    unsigned long newWlen = strlen(newW);
    unsigned long oldWlen = strlen(oldW);
  
    // сколько раз старое слово встретилось
    for (i = 0; s[i] != '\0'; i++)
    {
        if (strstr(&s[i], oldW) == &s[i])
        {
            cnt++;
  
            i += oldWlen - 1;
        }
    }
  
    // новая строка с нужной длиной
    result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1);
  
    i = 0;
    while (*s)
    {
        // сравнение подстроки и рузультата
        if (strstr(s, oldW) == s)
        {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }
  
    result[i] = '\0';
  printf("%s\n", result);
    free(result);
}
  


