#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_string(FILE *in) {
    char buf[1024];
    char *s = fgets(buf, 1024, in);
    if(s) {
        int len = strlen(s);
        int tmp = 0;
        char *res = malloc(len+1);
        while(s) {
            strcpy(res+tmp, s);
            if(s[strlen(s)-1] == '\n') break;
            s = fgets(buf, 1024, in);
            if (s) {
                tmp = strlen(s);
                len += tmp;
                res = realloc(res, len+1);
            }
        } 
        return res;
    } 
    return NULL;
}


int main(void){
    FILE *inp, *out;
    char *str, *res = NULL, *word;
    int word_len = 0, res_len, word_memory = 1;

    if ((inp = fopen("input.txt", "r")) == NULL) {
        printf("ERROR\n");
        return -1;
    }
    
    if ((out = fopen("out.txt", "w")) == NULL) {
        printf("ERROR\n");
        fclose(inp);
        return -1;
    }

    word = malloc(word_len+1);
    word[word_len] = '\0';
    while (str = read_string(inp)) {
        if (str[0] == '\n') continue;
        int len = strlen(str);
        int flag = 0;
        word_len = 1;
        int word_i = 0;
        for (int i = 0; i < len+1; i++, word_i++) {
            if(str[i] == ' ' || str[i] == '\t' || str[i] == '\0') {
                while(str[i] == ' ' || str[i] == '\t') {
                    i++;
                }
                if (flag) {
                    if(!res || !strstr(res, word)){
                        word_len = strlen(word);
                        if(!res) {
                            res = malloc(word_len+1);
                            strcpy(res, word);
                            res[word_len] = '\0';
                        } else {
                            res_len = strlen(res);
                            res = realloc(res, res_len + word_len + 2);
                            res[res_len] = '\n';
                            strcpy(res+res_len + 1, word);
                            res[res_len + word_len + 1] = '\0';
                        }
                    }
                }
                if (str[i] != '\0') i--;
                word_i = -1;
            } else {
                if(word_i+1 > word_memory) {
                    word_memory *= 2;
                    word = realloc(word, word_memory);
                }
                if (str[i] != '\n') {
                    word[word_i] = str[i];
                    word[word_i+1] = '\0';
                    flag = 1;
                }
            }
        }
        free(str);
    }
    fprintf(out, "%s", res);
    free(res);
    free(word);
    fclose(inp);
    fclose(out);
    return 0;
}
