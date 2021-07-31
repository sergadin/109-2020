#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "5.h"





void func(FILE *input, FILE *output)
{   double count[256];
    unsigned long maxlength=0;
    unsigned long minlength=1024;
    unsigned long summa_dlin_slov=0,kolichestvo_slov=1;
    double result;
    
    char * string = NULL;
    size_t len = 0;
    ssize_t read;
    unsigned int ASCII;
   
    for (int i=0;i<256;i++)
        count[i]=0;
    
    while ((read = getline(&string, &len, input)) != -1)
      {
         for(int i = 0; i < strlen(string); i++)
             {
                ASCII = string[i];
                count[ASCII]++;
             }
       
        char *temp = strtok(string, " ");
        while (temp != NULL)
             {
                
            
            summa_dlin_slov = summa_dlin_slov + strlen(temp);
            kolichestvo_slov++;
          
            if (strlen(temp) > maxlength)
            maxlength = strlen(temp);
            
            if (strlen(temp) < minlength)
            minlength = strlen(temp);
              
            temp = strtok(NULL, " ");
          }
          
        
      }
  
    result = (summa_dlin_slov)/kolichestvo_slov;
    
    fprintf(output,"average length: %f\n",result);
    fprintf(output,"max length: %lu\n", maxlength);
    fprintf(output,"min length: %lu\n", minlength);
  
    fputs("character   frequency", output);
    for (int k = 0; k <= 256; k++)
      {
        if (count[k] != 0)
        {   count[k]= count[k]/summa_dlin_slov*100;
           fprintf(output, "\n%c\t\t\t%.2f", k,count[k]);
        }

      }
   
}




