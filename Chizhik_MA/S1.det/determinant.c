#include <stdio.h>
#include <stdlib.h>

#include "../lib/ustrings.h"
#include "../lib/umath.h"
#include "determinant.h"

void find_determinant(char **matrix, int n, FILE *output) {
	int sign;
	int perm[n];
	int fact = factorial(n);

	for (int k = 0; k < n; k++) {
		perm[k] = k;
	}

	print_addendum(matrix, perm, 0, n, output);
	for (int i = 1; i < fact; i++) {
		int k, temp;
		for (int j = n - 2; j >= 0; j--) {
			if (perm[j] < perm[j + 1]) {
				k = n - 1;
				while (perm[j] > perm[k]) {
					k--;
				}
				temp = perm[k];
				perm[k] = perm[j];
				perm[j] = temp;
				inverse(perm + (j + 1), n - (j + 1));

				break;
			}
		}
		print_addendum(matrix, perm, i, n, output);
	}
	fprintf(output, "\n");
}

int perm_sign(int *arr, int n) {
	int sign = 1;
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (arr[i] > arr[j]) {
				sign *= -1;
			} else if (arr[i] == arr[j]) {
				return 0;
			}
		}
	}
	return sign;
}

void inverse(int *arr, int n) {
	for (int i = 0; i < n / 2; i++) {
		int swap = arr[i];
		arr[i] = arr[(n - 1) - i];
		arr[(n - 1) - i] = swap;
	}
}

void print_addendum(char **matrix, int *perm, int number, int n, FILE *output) {
	int sign = perm_sign(perm, n);
	if (number > 0) {
		fprintf(output, " ");
	}
	if (sign == -1) {
		fprintf(output, "- ");
	} else if ((sign == 1) && (number > 0)) {
		fprintf(output, "+ ");
	}

	fprintf(output, "%s", matrix[perm[0]]);
	for (int i = 1; i < n; i++) {
		fprintf(output, " * %s", matrix[(i * n) + perm[i]]);
	}
}

void free_1d_matrix(char **matrix, int order) {
	for (int i = 0; i < order * order; i++) {
		free(matrix[i]);
	}
	free(matrix);
}
