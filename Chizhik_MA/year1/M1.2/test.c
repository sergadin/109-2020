#include <stdio.h>
#include <stdlib.h>

#include "../lib/umath.h"
#include "determinant.h"

#define in "input.txt"
#define M 5
#define EPS 1e-6

int main(void) {
	int n;
	double *matrix, determinant, answer;
	FILE *input;

	if ((input = fopen(in, "r")) == NULL) {
		fprintf(stderr, "Can't open %s\n", in);
		return -1;
	}

	for (int k = 0; k < M; k++) {
		fprintf(stdout, "\nTest %d\n\n", k + 1);
		if (fscanf(input, "%d", &n) != 1) {
                        fprintf(stderr, "Can't read the order of the matrix\n");

                        fclose(input);
                        return -1;
                } else if (n <= 0) {
                        fprintf(stderr, "Err... Empty matrix? I don't like it\n");
                        fclose(input);
                        return -1;
                }

                if ((matrix = (double *)malloc(n * n * sizeof(double))) == NULL) {
                        fprintf(stderr, "Malloc can't allocate memory\n");

                        fclose(input);
                        return -1;
                }

		for (int i = 0; i < n * n; i++) {
                	if (fscanf(input, "%lf", &matrix[i]) != 1) {
                        	fprintf(stderr, "Can't read matrix of the given order\n");

                        	fclose(input);
	                        free(matrix);
        	                return -1;
                	}
        	}

        	determinant = find_determinant(matrix, n, EPS / n);
        	fprintf(stdout, "Computed: %lf\n", determinant);
		if (fscanf(input, "%lf\n", &answer) != 1) {
			fprintf(stderr, "Can't read the correct answer\n");
			free(matrix);
			fclose(input);
			return -1;
		}
		fprintf(stdout, "Expected: %lf\n", answer);
		if (compareDoubles(answer, determinant, EPS) == 0) {
			fprintf(stdout, "The difference is inconsiderable\n");
		} else {
			fprintf(stderr, "Something went wrong...\n");
			free(matrix);
			fclose(input);
			return -2;
		}

		free(matrix);
	}

	fprintf(stdout, "So, all the tests have been passed successfully, the program's output is correct\n");

	fclose(input);
	return 0;
}
