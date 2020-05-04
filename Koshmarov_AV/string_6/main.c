#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "help.h"

#define L 1024

int main() {
    FILE *input = fopen("input.txt", "r");
    int j, check;
    char *helper;
    char *help_point;
    char **arr_string = NULL;
    arr_string = malloc(L);
    arr_string[0] = read_string(input);

    for (int i = 1; i < L; i++){
        check = 0;
        helper = read_string(input);
        if (helper != NULL){
            arr_string[i] = helper;     //Считываем очередное слово

            j = i - 1;      //Начинаем проверку с предыдущего слова в массиве

            while (strcmp(arr_string[j], arr_string[i]) > 0){
                check = 1;
                j -= 1;
                if (j < 0)
                    break;
            }
            if (check == 1) {      //Если слово не должно стоять на последнем месте...
                j += 1;
                help_point = arr_string[j];
                arr_string[j] = arr_string[i];
                for (int k = i; k > j + 1; k--) {
                    arr_string[k] = arr_string[k - 1];
                }
                arr_string[j + 1] = help_point;
            }

        } else {
            j = i;
            break;
        }
    }

    for (int i = 0; i < j; i++){
        printf("%s\n", arr_string[i]);
        free(arr_string[i]);
    }
    free(arr_string);
    fclose(input);

    return 0;
}
