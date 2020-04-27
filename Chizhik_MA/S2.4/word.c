#include <stdio.h>
#include <stdlib.h>

#include "../lib/ustrings.h"
#include "word.h"

void find_word(FILE *input, FILE *output, const char *word) {
	int curr_str = 0;
	char *temp, *curr_p, *substring;
	while (!((temp = read_string(input)) == NULL)) {
		int curr_len, str_len = string_length(temp);
		curr_str++;
		curr_p = temp;

		while (((curr_len = string_length(curr_p)) > 0) && 
		       ((substring = substr(curr_p, word)) != NULL)) {
			int substr_pos = (int)(substring - curr_p) + 1;
			fprintf(output, "%d-%d\n", curr_str, (str_len - curr_len) + substr_pos);
			curr_p = substring + string_length(word);
		}
		
		free(temp);
	}
}
