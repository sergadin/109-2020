#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "2.h"

int main(void)

{
    FILE *input;
    
    char oldW[] = "replaceme";
    char newW[] = "YOUAREREPLACED";
    int lines_count;

    
    if((input = fopen("input.txt", "r")) == NULL) {
           printf("Не удалось открыть input.txt\n");
           return -1;
       }
  
    while (! feof(input))
       {
           if (fgetc(input) == '\n')
               lines_count++;
       }
    
    rewind(input);
    
    for (int i = 0; i <lines_count+1; i++)
        
       {   char *line;
           char *result;
           line=read_long_string(input);
           replace(line, oldW, newW);
           
       }
     fclose(input);
    //fclose(output);
    return 0;
   
}
