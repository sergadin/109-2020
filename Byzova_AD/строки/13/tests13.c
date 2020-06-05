//13. вводят строку нужно найти сдвиг исходной строки, такую что получившаяся строка минимальна в лексикографическом порядке
//без выделения памяти 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "13.h"


int main(void) {
    FILE *input, *output;
	int shift = 0;

//	char *str;

	if (( input = fopen("input.txt" , "r")) == NULL ) {
		printf ("Не удалось открыть файл") ;
		return -1;
	}
	if (( output = fopen("output.txt" , "w")) == NULL ) {
    		printf ("Не удалось открыть файл") ;
        	fclose(input);
			return -1;
	}  
	
	shift = solve(output, input);
	if(shift == -1) 
		printf("ERRRRROOOOORRR");
	else	
		printf("\nсдвиг  = %d", shift);
	

	fclose(input);
	fclose(output);
    return 0;
}
