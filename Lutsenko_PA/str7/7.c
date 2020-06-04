#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "7.h"





void func(FILE *input, FILE *output)
{   
    
    char * string = NULL;
    size_t len = 0;
    ssize_t read;
   
    
    while ((read = getline(&string, &len, input)) != -1)
        
      {fprintf(output,"Разрежем эту строку: %s\n",string);
        char *temp = strtok(string, " ");
        
        while (temp != NULL)
             { fprintf(output,"%s\n",temp);
                
                temp = strtok(NULL, " ");
              }
          
        
      }
  
    
   
}




