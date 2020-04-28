#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *s;
	FILE *input;
	s = (char*)malloc(4 * sizeof(char));
	input = fopen("input.txt", "r");
	fscanf(input, "%s", s);
	printf("%s", s);
	free(s);
	fclose(input);
	return 0;
}
