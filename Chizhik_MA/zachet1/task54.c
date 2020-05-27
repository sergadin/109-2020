#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/ustrings.h"
#include "task54.h"

/*
 * Функция суммирования элементов
 *
 * Параметры:
 * string_k: пирбавляемый элемент
 * string_p: изменяемый элемент
 *
 * Функция прибавляет одну строчку к другому по заданному правилу.
 *
 */

static void sum_elements(char *string_k, char *string_p) {
	int len_k, len_p;
	len_k = strlen(string_k), len_p = strlen(string_p);

	for (int i = 0; i < len_p; i++) {
		for (int j = 0; j < len_k; j++) {
			if (string_p[i] == string_k[j]) {
				for (int k = i + 1; k <= len_p; k++) {
					string_p[k - 1] = string_p[k];
				}
				len_p--;
				i--;
				break;
			}
		}
	}
}

char *inverse(char *word) {
	char *inversed;
	int len = strlen(word);
	if ((inversed = (char *)malloc(len + 1)) == NULL) {
		return NULL;
	}
	
	for (int i = 0; i < len; i++) {
		inversed[i] = word[len - 1 - i];
	}

	inversed[len] = 0;
	fprintf(stdout, "Inversed: %s\n", inversed);
	return inversed;
}

char *row_to_string(char **row, int len) {
	char *string = NULL;
	int curr_len = 1;

	if (len < 1) {
		return NULL;
	}

	for (int i = 0; i < len; i++) {
		if ((string = realloc(string, curr_len + strlen(row[i]))) == NULL) {
			return NULL;
		}
		strcpy(string + (curr_len - 1), row[i]);
		curr_len += strlen(row[i]);
	}

	fprintf(stdout, "String from row: %s\n", string);

	return string;
}

int find_row(char **matrix, int m, int n) {
	char *word, *inv_string;
	int row_index = -1;
	for (int i = 0; i < m; i++) {
		word = row_to_string(matrix + (i * n), n);
		for (int j = 0; j < n; j++) {
			inv_string = inverse(matrix[i * n + j]);
			if (strstr(word, inv_string) != NULL) {
				row_index = i;
				free(inv_string);
				break;
			}
			free(inv_string);
		}
		free(word);
		if (row_index != -1) break;
	}
	return row_index;
}

void add_row(char **matrix, int n, int k, int p) {
	for (int i = 0; i < n; i++) {	
		fprintf(stdout, "Before: %s\n", matrix[p * n + i]);
		sum_elements(matrix[k * n + i], matrix[p * n + i]);
		fprintf(stdout, "%d\n", strlen(matrix[p*n+i]));	
		fprintf(stdout, "After: %s\n", matrix[p * n + i]);
	}
}

void free_1d_matrix(char **matrix, int m, int n) {
	for (int i = 0; i < m * n; i++) {
		free(matrix[i]);
	}
	free(matrix);
}
