#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define L 1024

char *coup_string(char *stroka){
    int len = strlen(stroka);
    char *result = malloc(len + 1);
    for (int i = len - 1; i >= 0; i--){
        result[len - i - 1] = stroka[i];
    }
    return result;
}

