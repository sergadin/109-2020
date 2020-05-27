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
    };
    k = find(matrix, n, m);
    fun(matrix, n, m, k);
    print(matrix, n, m, output);
    free(matrix);
    fclose(input);
    fclose(output);
    return 0;
}
