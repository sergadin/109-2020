#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "help.h"

#define L 1024
#define k 3
#define q 5

int main() {
    int n, m;
    int len;
    int dop_len;
    int count;
    int num_of_str = -1;
    char *pozition;
    FILE *input;
    input = fopen("input.txt",     "r");
    if (input == NULL)
        return -1;
    if (fscanf(input, "%d", m) == EOF)
        return -1;
    if (fscanf(input, "%d", n) == EOF)
        return -1;
    char *a[m*n];
    for (int i = 0; i < n * m; i++){
        a[i] = get_string(input);
        if (a[i] == NULL)
            return -1;
    }
    char *w = coup_string(a[k*n + q]);
    char *slovo;

    for (int i = 0; i < m; i++){
            len = 0;
            count = 0;
            for (int j = 0; j < n; j++)
                len = len + strlen(a[i*n + j]);
            slovo = malloc(len + 1);
            for (int j = 0; j < n; j++){
                dop_len = strlen(a[i*n + j]);
                for(int p = 0; p < dop_len; p ++)
                    slovo[count + p] = a[i*n + j][p];
                count += dop_len;
            }
            if(strstr(slovo, w) != NULL){
                num_of_str = i;
                free(slovo);
                break;
            }
        free(slovo);
    }

    for (int i = 0; i < m; i++){
        if (i != num_of_str)
            for (int j = 0; j < n; j++){
                for(int h = 0; h < strlen(a[num_of_str*n + j]); h++) {
                    pozition = strchr(a[i * n + j], a[num_of_str * n + j][h]);
                    while (pozition != NULL) {
                        delete_char(a[i * n + j], pozition - a[i * n + j]);
                        pozition = strchr(a[i * n + j], a[num_of_str * n + j][h]);
                    }
                }
            }
    }

    FILE *result = fopen("result.txt", "w");
    fprintf(result, "%d, %d\n", m, n);
    for (int i = 0; i < n*m; i ++){
        fprintf(result, "%s\n", a[i]);
        free(a[i]);
    }
    fclose(input);
    fclose(result);

    return 0;
}
