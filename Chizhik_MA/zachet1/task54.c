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

	return string;
}

int find_in_the_row(char **row, int n, const char *needle) {
	int len = 0, sub_len;
	int curr_len;
	int words_ahead = 0, past_len = 0;

	for (int i = 0; i < n; i++) {
		len += strlen(row[i]);
	}
	sub_len = strlen(needle);
	curr_len = strlen(row[0]);

	for (int i = 0; i < len - sub_len + 1; i++) {
		unsigned int found = 1;
		if (i == curr_len) {
			words_ahead++;
			past_len += curr_len;
			curr_len = strlen(row[words_ahead]);
		}
		for (int j = 0; j < sub_len; j++) {
			if (row[words_ahead][i - past_len + j] != needle[j]) {
				found = 0;
				break;
			}
		}
		if (found == 1) {
			return i;
		}
	}

	return -1;
}

int find_row(char **matrix, int m, int n) {
	char *inv_string;
	int row_index = -1;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			inv_string = inverse(matrix[i * n + j]);
			if (find_in_the_row(matrix + (i * n), n, inv_string) != -1) {
				row_index = i;
				free(inv_string);
				break;
			}
			free(inv_string);
		}
		if (row_index != -1) break;
	}
	return row_index;
}

void add_row(char **matrix, int n, int k, int p) {
	for (int i = 0; i < n; i++) {	
		sum_elements(matrix[k * n + i], matrix[p * n + i]);
	}
}

void free_1d_matrix(char **matrix, int m, int n) {
	for (int i = 0; i < m * n; i++) {
		free(matrix[i]);
	}
	free(matrix);
}
