#include <stdio.h>
#include <stdlib.h>
#include "5.h"
#include <string.h>

int main(void)

{
    FILE *input;
    FILE *output;
    
  
    if((input = fopen("input.txt", "r")) == NULL) {
        printf("Не удалось открыть input.txt\n");
        return -1;
    }
    if((output = fopen("output.txt", "w")) == NULL) {
          printf("Не удалось открыть input.txt\n");
          fclose(input);
         return -1;
    }
    
    
    func(input, output);

    fclose(input);
    fclose(output);
    return 0;
   
}
