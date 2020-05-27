#include <stdlib.h>
#include <string.h>


char *delete_char(char *stroka, int pozition){
    int len = strlen(stroka);
    char *new_string = malloc(len);
    for (int i = 0; i < pozition; i++)
        new_string[i] = stroka[i];
    for (int i = pozition; i < len; i++)
        new_string[i-1] = stroka[i];
    return new_string;
}