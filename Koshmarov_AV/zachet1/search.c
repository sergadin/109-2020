#include <stdlib.h>
#include <string.h>
#include "help.h"


int search(char *stroka, char *mas[], int num_str, int n){
    char *pozition;
    int number;
    for (int j = 0; j < n; j++) {
        pozition = strchr(mas[num_str * n + j], stroka[0]);
        if (pozition != NULL) {
            number = pozition - mas[num_str * n + j];
            if (func(0, number, mas[num_str*n + j], stroka) == 1){
                return 1;
            }
        }
    }
    return 0;

}

