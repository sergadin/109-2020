#include <stdio.h>

#include "word.h"

#define in "input.txt"
#define out "output.txt"

int main(void) {
	FILE *input, *output;

	if ((input = fopen(in, "r")) == NULL) {
		fprintf(stderr, "Can't read %s\n", in);
		return -1;
	}

	if ((output = fopen(out, "w")) == NULL) {
		fprintf(stderr, "Can't write in %s\n", out);
		fclose(input);
		return -1;
	}

	find_word(input, output, "dolor");

	fclose(input);
	fclose(output);
	return 0;
}
