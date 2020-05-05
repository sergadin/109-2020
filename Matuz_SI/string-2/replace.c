#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "replace.h"



void read_file(FILE *file, char **data, size_t bufsize, int *array_size)
{
    int i = 0;
    data[0] = NULL;
    while ((getline(&data[i], &bufsize, file)) != -1) 
    {
        //printf("%s", data[i]);
        data[i + 1] = NULL;
        i++;
    }
    *array_size = i;
    return;
}

void ReplaceWord(const char *s, const char *old, const char *new)
{
    char *result = NULL;
    int i, count = 0;
    int newlength = strlen(new);
    int oldlength = strlen(old);
    for (i = 0; s[i] != '\0'; i++)
    {
        if (strstr(&s[i], old) == &s[i])
        {
            count++;
            i += oldlength - 1;
        }
    }

    result = (char *)malloc(i + count * (newlength - oldlength) + 1);

    i = 0;
    while (*s)
    {
        if (strstr(s, old) == s)
        {
            strcpy(&result[i], new);
            i += newlength;
            s += oldlength;
        }
        else
            result[i++] = *s++;
    }
    result[i] = '\0';
    printf("%s", result);
    free(result);
}