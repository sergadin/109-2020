#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


char *read_string(FILE *in) {
    char buf[PATH_MAX];
    buf[0] = 0;
    char *s = fgets(buf, PATH_MAX, in);
    if(s) {
        int len = strlen(s);
        char *res = malloc(len + 1);
        strcpy(res, s);
        return res;
    }
    return NULL;
}


int main(void){
    FILE *inp = fopen("input.txt", "r");
    FILE *out = fopen("out.txt", "w");
    char *str;
    int flag = 0;
    while(str = read_string(inp)){
        int len = strlen(str);
        for(int i = 0; i < len; i++) {
            if(str[i] == ' ') {
                while(str[i] == ' ') {
                    i++;
                }
                if(flag){
                    fprintf(out, "\n");
                }
                i--;
            } else {
                if(str[i] != '\n') {
                    fprintf(out, "%c", str[i]);
                    flag = 1;
                }
            }
        }
        free(str);
    }
    
    fclose(inp);
    fclose(out);
    return 0;
}
