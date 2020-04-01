#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../lib/umath.h"
#include "system.h"

#define M 3
#define EPS 1e-9
#define in "input.txt"

int main(void) {
	FILE *input;
	int n;
	double *solution, *answer;
	double **matrix;
	Status s;

	if ((input = fopen(in, "r")) == NULL) {
		fprintf(stderr, "Can't open %s\n", in);
		return -1;
	}

	for (int k = 0; k < M; k++) {
		fprintf(stdout, "\nTest %d\n\n", k + 1);
		if (fscanf(input, "%d", &n) != 1) {
			fprintf(stderr, "Can't read order of the coefficient matrix\n");
			fclose(input);
			return -1;
		} else if (n <= 0) {
			fprintf(stderr, "Your matrix must be empty. It's pointless\n");
			fclose(input);
			return -1;
		}

		if ((matrix = (double **)malloc(n * sizeof(double *))) == NULL) {
			fprintf(stderr, "Malloc can't allocate memory\n");
			fclose(input);
			return -1;
		}

		for (int i = 0; i < n; i++) {
			if ((matrix[i] = (double *)malloc((n + 1) * sizeof(double))) == NULL) {
				fprintf(stderr, "Malloc can't allocate memory for string %d\n", i + 1);
				for (int j = 0; j < i; j++) {
					free(matrix[j]);
				}
				free(matrix);
				fclose(input);
				return -1;
			}
		}

		for (int a = 0; a < n; a++) {
			for (int b = 0; b < n + 1; b++) {
				if (fscanf(input, "%lf", &(matrix[a][b])) != 1) {
					fprintf(stderr, "Can't read the matrix properly\n");
					clear_two_dimensional_matrix(matrix, n);
					fclose(input);
					return -1;
				}
			}
		}

		solution = solve_system(matrix, n, EPS, &s);
		if (s == CANNOT_ALLOCATE_MEMORY) {
			fprintf(stderr, "Malloc can't allocate memory for solution");
			clear_two_dimensional_matrix(matrix, n);
			fclose(input);
			return -1;
		}
		
		if ((answer = (double *)malloc(n * sizeof(double))) == NULL) {
			fprintf(stderr, "Malloc can't allocate memory for correct answer\n");
			clear_two_dimensional_matrix(matrix, n);
			free(solution);
			fclose(input);
			return -1;
		}

		for (int l = 0; l < n; l++) {
			if (fscanf(input, "%lf", &answer[l]) != 1) {
				fprintf(stderr, "Can't read the answer\n");
				free(solution);
				free(answer);
				clear_two_dimensional_matrix(matrix, n);
				fclose(input);
				return -1;
			}
		}

		switch(s) {
			case NOT_DETERMINED:
				fprintf(stdout, "The system has infinitely many solutions or doesn't have them at all\n");
				break;
			case OK:
				fprintf(stdout, "Solution of the system:\n");
				for (int c = 0; c < n; c++) {
					fprintf(stdout, "x_%d = %lf\n", c + 1, solution[c]);
					if (compareDoubles(solution[c], answer[c], EPS) != 0) {
						fprintf(stderr, "\nWait... The answer's not correct\n");
						free(solution);
						free(answer);
						clear_two_dimensional_matrix(matrix, n);
						fclose(input);
						return -1;
					}
				}
				fprintf(stdout, "\nAnd it is absolutely correct!\n");
				break;
		}

		clear_two_dimensional_matrix(matrix, n);
		free(solution);
		free(answer);
	}

	fprintf(stdout, "So, all the tests have been passed successfully. We now can solve systems of linear equations\n");

	fclose(input);
	return 0;
}
