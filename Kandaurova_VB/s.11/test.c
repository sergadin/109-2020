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
   // s = malloc(argc * sizeof(char *));
	if((input = fopen("input.txt", "r")) == NULL) {
        printf("Не удалось открыть input.txt\n");
		return -1;
    }
    //for(int i = 2; i < argc; i++) 
    //    printf("%s %d\n", argv[i], strlen(argv[i]));
	ifdef(input, argv, argc);
	fclose(input);
	return 0;
}
