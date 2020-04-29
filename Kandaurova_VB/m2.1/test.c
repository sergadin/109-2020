#include <stdio.h>
#include <stdlib.h>
#include "rank.h"

int main(void) {
	FILE *input;
	int n_row = 8, n_col = 8, ans, true = 6;
	double el, eps = 0.0001;
	double **matrix = (double **)malloc(n_row * sizeof(double *));
	if((input = fopen("input.txt", "r")) == NULL) {
        printf("Не удалось открыть файл\n");
		return -1;
    }
	for(int i = 0; i < n_row; i++) {
		matrix[i] = (double *)malloc(n_col * sizeof(double));
	}
	for(int i = 0; i < n_row; i++) {
		for(int j = 0; j < n_col; j ++) {
			if(fscanf(input, "%lf", &el) != 1) {
                printf("Не удалось прочитать элемент\n");
				return -1;
            }
			matrix[i][j] = el;
		}
	}
	ans = mrank(matrix, n_row, n_col, eps);
	printf("answer: %d\ntrue answer: %d\n", ans, true);
	for(int i = 0; i < n_row; i++)
		free(matrix[i]);
	free(matrix);
    fclose(input);
}
