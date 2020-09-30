//12. Отформатировать абзацы текста в заданных границах и с красной строкой (без переноса слов). Абзац — фрагмент текста между пустыми строками.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "12.h"


int main(void) {
    FILE *input, *output;
	int k = 0;

	if (( input = fopen("input.txt" , "r")) == NULL ) {
		printf ("Не удалось открыть файл") ;
		return -1;
	}
	if (( output = fopen("output.txt" , "w")) == NULL ) {
    		printf ("Не удалось открыть файл") ;
        	fclose(input);
			return -1;
	}  
	
	k = solve_one (output, input);
	if(k == -1) 
		printf("ERRRRROOOOORRR");
	printf("k = %d", k);
	

	fclose(input);
	fclose(output);
    return 0;
}
