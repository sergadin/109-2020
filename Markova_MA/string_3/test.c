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
		int past_len = 0;
        char *res = malloc(len+1);
        while(s) {
            strcpy(res+past_len, s);
            if(s[strlen(s)-1] == '\n') break;
            s = fgets(buf, 1024, in);
            if (s) {
                tmp = strlen(s);
			past_len = len;
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
    char *str, *stock = NULL, *w;
    if ((inp = fopen("input.txt", "r")) == NULL) {
        printf("ERROR\n");
        return -1;
    }
    if ((out = fopen("output.txt", "w")) == NULL) {
        printf("ERROR\n");
        fclose(inp);
        return -1;
    }
    int len_w = 0, stock_len = 0, w_memory = 1;
    w = malloc(len_w+1);
    w[len_w] = '\0';
    while (str = read_string(inp)) {
        if (str[0] == '\n') continue;
        int len = strlen(str);
        if (str[len - 1] == '\n') {
            str[len - 1] = '\0';
            len--;
        }
        len_w = 0;
        int w_i = 0;
        for (int i = 0; i < len + 1; i++, w_i++) {
            if(str[i] == ' ' || str[i] == '\t' || str[i] == '\0') {
                if (len_w > 0) {
                    if(!stock || !strstr(stock, w)){
                        stock = realloc(stock, stock_len + len_w + 2);
                        strcpy(stock + stock_len, w);
                        stock[stock_len + len_w] = '\n';
                        stock[stock_len + len_w + 1] = '\0';
                        stock_len += len_w + 1;
                    }
                }
                w_i = -1;
                len_w = 0;
            } 
			else { 
                if(w_i+1 > w_memory) {
                    w_memory *= 2;
                    w = realloc(w, w_memory);
                }
                w[w_i] = str[i];
                w[w_i+1] = '\0';
                len_w++;
            }
        }
        free(str);
    }
    fprintf(out, "%s", stock);
    free(stock);
    free(w);
    fclose(inp);
    fclose(out);
    return 0;
}
