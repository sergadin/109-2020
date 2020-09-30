#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "7.h"





void func(FILE *input, FILE *output, int n)
{   
    
    char * string = NULL;
    size_t len = 0;
    ssize_t read;
    
   
    
    while ((read = getline(&string, &len, input)) != -1)
        
    {   fprintf(output,"\nРазрежем эту строку: %s\n",string);
        char *temp = strtok(string, " ");
        unsigned long sum_len = 0;
        fprintf(output,"\n%s",temp);
        int kolvoproberlov=0;
        temp = strtok(NULL, " ");
        while (temp != NULL)
        {
               sum_len = sum_len + strlen(temp)/2;
            kolvoproberlov++;
            if  (sum_len + kolvoproberlov-1  >= n)
            {
                fprintf(output,"\n");
                sum_len = strlen(temp);
                kolvoproberlov = 0;
            }
            
            fprintf(output," %s",temp);
           
          
                     
            
                temp = strtok(NULL, " ");
        }
          
        
      
    }
    
   
}




