#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    if ((inp = fopen("input.txt", "r")) == NULL) {
        printf("ERROR\n");
        return -1;
    }
    if ((out = fopen("out.txt", "w")) == NULL) {
        printf("ERROR\n");
        fclose(inp);
        return -1;
    }
    char *str, *res = NULL, *word;
    int word_len = 0, res_len = 0, word_memory = 1;
    word = malloc(word_len+1);
    word[word_len] = '\0';
    while (str = read_string(inp)) {
        if (str[0] == '\n') continue;//if it's just an empty string without words, then skip it
        int len = strlen(str);
        if (str[len-1] == '\n') {
            str[len-1] = '\0';
            len--;
        }
        word_len = 0;
        int word_i = 0;
        for (int i = 0; i < len+1; i++, word_i++) { //we go along the string by symbols
            if(str[i] == ' ' || str[i] == '\t' || str[i] == '\0') { //checked at the end of the word, check on '\0' need to add the last word in the string
                if (word_len > 0) {
                    if(!res || !strstr(res, word)){ //if this word is not yet there, or there were no words at all
                        res = realloc(res, res_len + word_len + 2);
                        strcpy(res+res_len, word);
                        res[res_len + word_len] = '\n';
                        res[res_len + word_len + 1] = '\0';
                        res_len += word_len + 1;
                    }
                }
                word_i = -1;
                word_len = 0;
            } else { //make up the word
                if(word_i+1 > word_memory) {
                    word_memory *= 2;
                    word = realloc(word, word_memory);
                }
                word[word_i] = str[i];
                word[word_i+1] = '\0';
                word_len++;
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
