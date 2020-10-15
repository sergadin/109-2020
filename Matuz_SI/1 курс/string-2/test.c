#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "replace.h"


int main(void) {
    FILE *input;//, *output;
    int size = 0;
    size_t bufsize = 32;
    char **data;
    data = malloc(bufsize * sizeof(char *));

    char old[] = "bla";
    char new[] = "cool";


    if ((input = fopen("input.txt", "r")) == NULL) 
    {
        printf("cannot open input file\n");
        return -1;
    }

    /*if ((output = fopen("output.txt", "r")) == NULL)
    {
        printf("cannot open output file\n");
        fclose(input);
        return -1;
    }*/

    read_file(input, data, bufsize, &size);

    for (int i = 0; i < size; i++)
    {
        printf("%s", data[i]);
    }
    printf("\n////////////////\n");
    for (int i = 0; i < size; i++)
    {
        ReplaceWord(data[i], old, new);
    }
    printf("\n");
    
    //printf("\n %d", size);
    fclose(input);
    //fclose(output);

    for (int i = 0; i <= size; i++)
    {
	free(data[i]);
    }
    free(data);
    return 0;
}