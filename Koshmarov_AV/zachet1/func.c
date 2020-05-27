#include <stdlib.h>
#include <string.h>

int func(int pozition_in_slovo, int pozition_in_al_mas, char **el_mas, char *slovo, int n, int j, int num_str ){
    for (int i = pozition_in_slovo; i < strlen(slovo); i++){
        if (el_mas[num_str * n + j][i - pozition_in_slovo + pozition_in_al_mas] != '\0'){
            if (el_mas[num_str * n + j][i - pozition_in_slovo + pozition_in_al_mas] == slovo[i]){
                continue;
            } else {
                return 0;
            }
        } else {
            if (j < n){
                return func(i, 0, el_mas, slovo, n, j+1, num_str);
            } else
                return 0;
        }
    }
    return 1;
}