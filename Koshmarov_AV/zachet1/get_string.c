#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define L 1024

char *get_string(FILE *f){
    char buf[L];
    buf[0] = 0;
    char *s = fgets(buf, L - 1, f);
    if(s){
        int length = strlen(s);
        char *result = malloc(length + 1);
        if (s[length - 1] == '\n'){
            for (int i = 0; i < length - 1; i++) {
                result[i] = s[i];
            }
        }
        else {
            strcpy(result, buf);
        }
        return result;
    }
    return NULL;
}