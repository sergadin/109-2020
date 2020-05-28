#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readstring(FILE *input);
int find(char *s, char *w); //проверяет, начинается ли строка s со строки w
int check(char *s, char **w, int n); //проверяет, содержит ли строка s какую-нибудь из строк w, начиная с 1

int check(char *s, char **w, int n) {
    int flag = 0, a;
    for(int i = 2; i < n; i++) {
        a = strcmp(s, w[i]);
        if(a == 0)
            flag = 1;        
    }
    return flag;
}

int find(char *s, char *w) {
    int flag = 1;
    for(int i = 0; i < strlen(w) - 1; i++) {
        if(s[i] != w[i]) {
            flag = 0;
            break;
        }
    }
    return flag;
}

char *readstring(FILE *f) {
	char buf[1024];
	buf[0] = 0;
	char *s = fgets(buf, 1024, f);
	if(s) { 
	    int len = strlen(s);
	    char *result = malloc(len);
		strcpy(result, s);
        result = realloc(result, len - 1);
        result[len - 1] = '\0';
        return result;
	}
	return NULL;
}

void ifdef(FILE *input, char **x, int n) {
    char *s, sif[7] = {"#ifdef"}, selse[6] = {"#else"}, send[7] = {"#endif"};
    int k, *stack = NULL, i = -1;
    while ((s = readstring(input)) != NULL) {
        if(find(s, sif) == 1) {
            i++;
            stack = realloc(stack, i * sizeof(int));
            if(check(s + 7, x, n) == 1) {
                stack[i] = 1;
            }
            else
                stack[i] = 0;
        }
        else if(find(s, selse) == 1) {
            if(stack[i] == 1)
                stack[i] = 0;
            else
                stack[i] = 1;
        }
        else if(find(s, send) == 1) {
            i--;
            if(i == -1)
                stack = NULL;
        }
        else if((i == -1) || (i >= 0) && (stack[i] == 1))
            printf("%s\n", s);
    } 
    free(stack);   
}
