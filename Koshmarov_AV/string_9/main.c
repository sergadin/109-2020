#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define len_inc 8
#define MAX_FILE_NAME 1024

int main() {
    FILE* stream;
    int trigger = 0;
    char a;
    char *inc;
    char *file_name;
    char *str1 = "include";
    inc = malloc(len_inc);
    while (scanf("%c", &a)){
        if (a == '#' || trigger == 1){      //trigger нужен, чтобы работали случаи #bla#include input.txt
            if (trigger == 0)
                scanf("%c", &a);
            trigger = 0;
            for (int i = 0; i < len_inc - 1; i++){
                if (a == '\n' || a == EOF)
                    break;
                if (a == '#'){
                    trigger = 1;
                    break;
                }
                inc[i] = a;
                scanf("%c", &a);
            }
            if (trigger == 1) {
                printf("#%s", inc);
                continue;
            }
            if (strcmp(str1, inc) == 0){    //если встретился #include
                scanf("%c", &a);
                printf("%c", a);
                file_name = malloc(MAX_FILE_NAME);
                while (a == ' ') {            //считываем все пробелы
                    scanf("%c", &a);
                    printf("%c", a);
                }
                for (int j = 0; j < MAX_FILE_NAME - 1; j++){    //считываем имя файла
                    file_name[j] = a;
                    scanf("%c", &a);
                    if (a == ' ' || a == EOF || a == '\n')
                        break;
                }

                stream = fopen(file_name, "r");
                if (stream == NULL) {
                    printf("\n\"%s\"  --  This file does not exist!", file_name);
                    free(file_name);
                    return 0;
                }
                fscanf(stream, "%c", &a);
                while (a != EOF){
                    printf("%c", a);
                    a = getc(stream);
                }
                free(file_name);
                fclose(stream);
            }
            else{                           //если после # не include
                printf("#%s", inc);
            }
        }
        else{
            printf("%c", a);
        }
    }
    return 0;
}
