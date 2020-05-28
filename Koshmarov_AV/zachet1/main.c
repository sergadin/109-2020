#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "help.h"

#define L 1024
#define k 1
#define q 0

int main() {
    int n, m;
    int len;
    int dop_len;
    int count;
    int num_of_str = -1;
    char *pozition;
    FILE *input;
    input = fopen("input.txt",     "r");
    if (input == NULL) {
        fclose(input);
        return -1;
    }
    if (fscanf(input, "%d", &m) == EOF) {
        fclose(input);
        return -1;
    }
    if (fscanf(input, "%d", &n) == EOF){
        fclose(input);
        return -1;
    }
    char *a[m*n];
    char *musor = get_string(input);
    for (int i = 0; i < n * m; i++){
        a[i] = get_string(input);
        if (a[i] == NULL){
            fclose(input);
            for (int j = 0; j < i; j++)
                free(a[j]);
            return -1;
        }
    }
    if(strlen(a[k*n + q]) != 0) {
        char *w = coup_string(a[k * n + q]);

        int number;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                pozition = strchr(a[i * n + j], w[0]);
                if (pozition != NULL) {
                    number = pozition - a[i * n + j];
                    if (func(0, number, a, w, n, j, i) == 1) {
                        num_of_str = i;
                        break;
                    }
                }
            }
        }
        if (num_of_str == -1) {
            fclose(input);
            for (int i = 0; i < n * m; i++)
                free(a[i]);
            free(w);
            return -1;
        }
        free(w);
    } else{
        return -1;
    }
    for (int i = 0; i < m; i++){
        if (i != num_of_str)
            for (int j = 0; j < n; j++){
                for(int h = 0; h < strlen(a[num_of_str*n + j]); h++) {
                    pozition = strchr(a[i * n + j], a[num_of_str * n + j][h]);
                    while (pozition != NULL) {
                        a[i * n + j] = delete_char(a[i * n + j], pozition - a[i * n + j]);
                        pozition = strchr(a[i * n + j], a[num_of_str * n + j][h]);
                    }
                }
            }
    }

    FILE *result = fopen("result.txt", "w");
    fprintf(result, "%d %d\n", m, n);
    for (int i = 0; i < n*m; i ++){
        fprintf(result, "%s\n", a[i]);
        free(a[i]);
    }
    fclose(input);
    fclose(result);

    return 0;
}
