#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include <string.h>

int main(int argc, char *argv[]) {
    char **s;
    FILE *input;
    if(argc == 1) {
        printf("Вы не ввели имя файла\n");  
        return 0;  
    }
	if((input = fopen("input.txt", "r")) == NULL) {
        printf("Не удалось открыть input.txt\n");
		return -1;
    }
	ifdef(input, argv, argc);
	fclose(input);
	return 0;
}
