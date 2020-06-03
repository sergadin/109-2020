#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "5.h"

#define MAX_WORD_LENGTH 20




void maxminlength(FILE *input, FILE *output)
{
  
    char str[60];
    
    char *largest = (char*) malloc (MAX_WORD_LENGTH);
    char *smallest = (char*) malloc (MAX_WORD_LENGTH);
    
    int smallest_len = MAX_WORD_LENGTH, largest_len = 0;

   


    while (fgets (str, 60, input) != NULL)
    {
        char *temp = strtok(str, " ");
        while (temp != NULL)
        {
            if (strlen(temp) > largest_len)
            {
                strcpy(largest, temp);
                largest_len = strlen(largest);
            }
            if (strlen(temp) < smallest_len)
            {
                strcpy(smallest, temp);
                smallest_len = strlen(smallest);
            }
            temp = strtok(NULL, " ");
        }
    }

    fprintf(output,"longest in the file: %s\n", largest);
    fprintf(output,"shortest in the file: %s\n", smallest);



   
}



void freq(FILE *input, FILE *output)
{
    int count[256] = { 0 };

    int k;

    int c;
    
    rewind(input);
    while((c=fgetc(input))) {

      if(c == EOF) break;

      count[c]+=1;
    }

     fputs("character    frequency", output);
     for (k = 0; k <= 256; k++)
       if (count[k] != 0)
           fprintf(output, "\n%c\t\t%2d", k, count[k]);
    
  
    
}



