#include <stdio.h>
#include "det.h"
#include <stdlib.h>

int main(void) {
	FILE *input;
	int n = 8;
	double ans, el, true = 2;
	double *matrix = (double *)malloc(n * n *  sizeof(double));
	if((input = fopen("input.txt", "r")) == NULL) {
        printf("Не удалось открыть файл\n");
		return -1;
    }
	for(int j = 0; j < n * n; j++) {
        if(fscanf(input, "%lf", &el) != 1) {
            printf("Не удалось прочитать элемент матрицы\n");
	        return -1;
        }
		matrix[j] = el;
    }
	ans = dete(matrix, n);
	printf("answer: %lf\ntrue answer: %lf\n", ans, true);
	free(matrix);
    fclose(input);
}
