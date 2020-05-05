#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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


int main(int argc, char *argv[]){
    FILE *inp, *out;
    char *start, *end;

    if ((inp = fopen("input.txt", "r")) == NULL) {
        printf("ERROR\n");
        return -1;
    }
    
    if ((out = fopen("out.txt", "w")) == NULL) {
        printf("ERROR\n");
        fclose(inp);
        return -1;
    }

    if (argc == 1) {
        start = malloc(2);
        end = malloc(2);
        start[0] = '"';
        start[1] = '\0';
        end[0] = '"';
        end[1] = '\0';
        printf("start quote: %s\nend quote: %s\n", start, end);
        printf("if you need other - enter %cquotes%c in command line arguments\n", '"', '"');
        
    } else if (argc == 2) {
        start = argv[1];
        end = argv[1];
    } else if (argc == 3) {
        start = argv[1];
        end = argv[2];
    } else {
        printf("Must be no more than 3 arguments\n");
        return 0;
    }
    char *begin_quotes, *end_quotes, *str, tmp;
    int start_quote_found = 0, end_quote_found = 0;
    while(str = read_string(inp)) {
        begin_quotes = strstr(str, start);
        if (begin_quotes && !start_quote_found) {
            start_quote_found = 1;
            char k = begin_quotes[0];
            begin_quotes[0] = '\0';
            fprintf(out, "%s", str);
            begin_quotes[0] = k;
            begin_quotes++;
            end_quotes = strstr(begin_quotes, end);
            if(end_quotes) {
                end_quote_found = 1;
                end_quotes += strlen(end);
                fprintf(out, "%s", end_quotes);
            }
        } else {
            end_quotes = strstr(str, end);
            if(end_quotes && !end_quote_found) {
                end_quotes += strlen(end);
                fprintf(out, "%s", end_quotes);
                end_quote_found = 1;
            } else if (!start_quote_found || end_quote_found) {
                fprintf(out, "%s", str);
            }
        }
        free(str);
    }
    if (!end_quote_found) {
        fclose(out);
        fclose(inp);
 
    if ((out = fopen("out.txt", "w")) == NULL) {
        printf("ERROR\n");        
        return -1;
    }

    if ((inp = fopen("input.txt", "r")) == NULL) {
        printf("ERROR\n");
        fclose(out);
        return -1;
    }
    
    
        while(str = read_string(inp)) {
            fprintf(out, "%s", str);
            free(str);
        }
    }
    
    if (argc == 1) {
        free(start);
        free(end);
    }
    
    fclose(inp);
    fclose(out);
    return 0;
}
