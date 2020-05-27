#include <stdio.h>
#include <stdlib.h>
#include "../lib/ustrings.h"
#include "task54.h"

static void print_usage(char *program_name) {
	fprintf(stderr, "usage: %s input.txt\n", program_name);
	fprintf(stderr, "input.txt: file with matrix\n");
}

int main(int argc, char **argv) {
	FILE *input, *result;
	char *input_filename;
	char **matrix;
	int m, n, special_row;
	unsigned int reading_success;

	if (argc > 1) {
		input_filename = argv[1];
	} else {
		print_usage(argv[0]);
		return -1;
	}

	if ((input = fopen(input_filename, "r")) == NULL) {
		fprintf(stderr, "Can't read %s\n", input_filename);
		return -1;
	}

	if ((result = fopen("result.txt", "w")) == NULL) {
		fprintf(stderr, "Can't open result.txt\n");
		fclose(input);
		return -1;
	}

	if (fscanf(input, "%d", &m) != 1) {
		fclose(input);
		fclose(result);
		
		return -1;
	}

	if (fscanf(input, "%d\n", &n) != 1) {
		fclose(input);
		fclose(result);

		return -1;
	}

	if ((matrix = (char **)malloc(m * n * sizeof(char *))) == NULL) {
		fclose(input);
		fclose(result);
		return -1;
	}

	for (int i = 0; i < m * n; i++) {
		matrix[i] = read_string(input);
		fprintf(stdout, "%s\n", matrix[i]);
	}

	special_row = find_row(matrix, m, n);
	if (special_row == -1) {
		fprintf(stdout, "Can't find such a string. Nothing has happened\n");
	} else {
		for (int i = 0; i < m; i++) {
			if (i == special_row) {
				continue;
			}
			fprintf(stdout, "special_row = %d, i = %d\n", special_row, i);
			add_row(matrix, n, special_row, i);
		}
	}

	fprintf(result, "%d %d\n", m, n);
	for (int i = 0; i < m * n; i++) {
		fprintf(result, "%d element: %s\n", i, matrix[i]);
	}

	fclose(input);
	fclose(result);
	free_1d_matrix(matrix, m, n);
	return 0;
}
