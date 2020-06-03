#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "2.h"

int main(int argc, char *argv[])

{
    FILE *input;
    int lines_count;
    char *oldW,*newW,*filename;
    
   if( (argc != 4) )
      {
          printf("формат ввода: имя файла(input.txt) - что заменить - чем заменить ");
          return -1;
      }
    
    filename = argv[1];
    oldW = argv[2];
    newW  = argv[3];
    

    
    if((input = fopen(filename, "r")) == NULL) {
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
           
           line=read_long_string(input);
           replace(line, oldW, newW);
           
       }
     fclose(input);
    //fclose(output);
    return 0;
   
}
