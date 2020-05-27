#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

int main(void) {
    int n, m, k, a;
    FILE *input, *output;
    char **matrix;
    if((input = fopen("input.txt", "r")) == NULL) {
        //printf("Не удалось открыть файл\n");
		return -1;
    }
    if((output = fopen("result.txt", "w")) == NULL) {
        free(input);
        //printf("Не удалось открыть файл\n");
		return -1;
    }
    if(fscanf(input, "%d %d\n", &n, &m) != 2) 
        return -1;
    matrix = (char **)malloc(n * m *  sizeof(char *));
    for(int i = 0; i < n * m; i++) {
        matrix[i] = readstring(input);
    }
    //printf("%s", matrix[3]);
    k = find(matrix, n, m);
    //printf("%d\n", k);
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            for(int t = 0; t < strlen(matrix[i * m + j]) - 1; t++) {
                a = 0;       
                for(int s = 0; s < strlen(matrix[k * m + j]); s++) {
                    if(matrix[i * m + j][t] == matrix[k * m + j][s]) {
                        a = 1;
                        break;
                    }                
                }
                if(a == 0) 
                    printf("%c", matrix[i * m + j][t]);
                /*if(strpbrk(&matrix[i * m + j][t], matrix[k * m + j]) != NULL) {
                    //printf("%c %s", matrix[i * m + j][t], matrix[k * m + j]);
                    printf("%c", matrix[i * m + j][t]);
                }*/
            }
            printf(" ");
        }
        printf("\n");
    }
    free(matrix);
    return 0;
}
