#include <stdio.h>
#include <stdlib.h>
#include "str.h"

int main(void) {
	FILE *input, *output;
	if((input = fopen("input.txt", "r")) == NULL) {
        printf("Не удалось открыть input.txt\n");
		return -1;
    }
	if((output = fopen("output.txt", "w")) == NULL) {
        printf("Не удалось открыть output.txt\n");
        fclose(input);
		return -1;
    }
	findstr(input, output, "who");
	fclose(input);
	fclose(output);
	return 0;
}
