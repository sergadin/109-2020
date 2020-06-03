#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "5.h"


int main(void) {
    FILE *input, *output;

	if (( input = fopen("input.txt" , "r")) == NULL ) {
		printf ("Не удалось открыть файл") ;
		return -1;
	}
	if (( output = fopen("output.txt" , "w")) == NULL ) {
    		printf ("Не удалось открыть файл") ;
        	fclose(input);
			return -1;
	}  
	
	solve_one (output, input);

    return 0;
}
	
