#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

int main(void) {
    int n, m, k;
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
    printf("%d\n", k);
    /*for(int i = 0; i < n; i++) {
        int b = 1;
        for(int j = 0; j < m; j++)
            b += strlen(matrix[i * m + j]) - 1;
        matr[i] = (char *)malloc(b * sizeof(char *));
        if(int j = 0; j < m; j++) 
            strcat(matr[i], matrix[i * m + j]);
    }*/
    //printf("%s%s", matrix[0], matrix[1]);
    //printf("%d\n", strlen(matrix[0]));
    free(matrix);
    return 0;
}
