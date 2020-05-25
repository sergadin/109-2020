#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readstring(FILE *input);
int find(char *s, char *w); //проверяет, начинается ли строка s со строки w
int check(char *s, char **w, int n); //проверяет, содержит ли строка s какую-нибудь из строк w, начиная с 1

int check(char *s, char **w, int n) {
    int flag = 1;
    for(int i = 2; i < n; i++) {
        if(strlen(s) >= strlen(w[i])) {
            for(int j = 0; j <= strlen(w[i]); j++) {
                if(s[j] != w[i][j]) {
                    flag = 0;
                    break;
                } 
            }
        }
        if(flag == 1)
            break;  
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
		char *result = malloc(len + 1);
		strcpy(result, s);
		return result;
	}
	return NULL;
}

void ifdef(FILE *input, char **x, int n) {
    char *s, sif[7] = {"#ifdef"}, selse[6] = {"#else"}, send[7] = {"#endif"};
    int k;
    while ((s = readstring(input)) != NULL) {
        if(find(s, sif) == 1) {
            if(check(s + 7, x, n) == 1) {
                if(find(s, selse) == 1) {
                    while ((s = readstring(input)) != NULL) {
                        if(find(s, send) == 1)
                            break;
                    }                    
                }
                else
                    printf("%s", s);
            }
            if(check(s + 7, x, n) == 0) {
                if(find(s, selse) == 0) {
                    while ((s = readstring(input)) != NULL) {
                        if(find(s, selse) == 1)
                            break;
                    }                    
                }
                else
                    printf("%s", s);
            }
            else
                printf("%s", s);
        }
    }    


    /*while ((s = readstring(input)) != NULL) {
        //printf("%s\n", s);
        if(find(s, sif) == 1) {
            if(check(s + 7, x, n) == 1) {
                    //printf("YY\n");
                    if(find(s, sif) == 1)
                        ifdef(input, x, n); 
                    if(find(s, selse) == 1) {
                        k = 1;
                        while((s = readstring(input)) != NULL) {
                            if(find(s, sif) == 1)
                                k++;
                            if(find(s, send) == 1)
                                k--;
                            if(k == 0)
                                break;
                        }
                    }                      
                    else 
                        printf("%s", s);
            }
            if(check(s + 7, x, n) == 0) {
                //printf("XX\n");
                k = 1;
                while ((s = readstring(input)) != NULL) {
                    if(find(s, sif) == 1)
                        k++;
                    if(find(s, send) == 1)
                        k--;
                    //printf("%d %s", k, s);
                    if(k == 0)
                        break;
                }
                k = 1;
                while ((s = readstring(input)) != NULL) {
                    if(find(s, sif) == 1)
                        k++;
                    if(find(s, send) == 1)
                        k--;
                    //printf("%d %s", k, s);
                    if(k == 0)
                        break;
                    //printf("%s %d\n", s, k);
                }
            }   
        }
        else 
            printf("%s", s);      
    }*/
}
