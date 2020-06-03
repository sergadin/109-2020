#include <stdio.h>
#include <stdlib.h>

int find( double *stroka, int n, int *error){
    double sr_arifm = 0;
    for (int i = 0; i < n; i++){
        sr_arifm += stroka[i];
    }
    sr_arifm = sr_arifm / n;
    for (int i = 0; i < n; i++){
        if (stroka[i] > sr_arifm)
            return i;
    }
    printf("Не выполняется условие поиска!\n");
    *error = 1;
    return 0;
}

double sr_ar(double *stroka, int n){
    double sr_ar = 0;
    for (int i = 0; i < n; i++){
        sr_ar += stroka[i];
    }
    sr_ar = sr_ar / n;
    return sr_ar;
}

int preobr(double *mas, int num_stroka, int m, int n){
    double sr;
    for(int i = 0; i < m; i++){
        sr = sr_ar(&mas[i*n], n);
        if (sr == 0){
            return 1;
        }
        for (int j = 0; j < n; j++){
            mas[i*n + j] = mas[num_stroka*n + j] / sr;
        }
    }
    return 0;
}


int main() {
    int m, n;
    int min, min_stroka;
    int error = 0;
    FILE *input;
    input = fopen("input.txt",     "r");
    if (input == NULL) {
        fclose(input);
        printf("Входной файл не найден!\n");
        return 0;
    }
    if (fscanf(input, "%d", &m) == 0) {
        printf("Ошибка ввода!\n");
        fclose(input);
        return 0;
    }
    if (fscanf(input, "%d", &n) == 0){
        printf("Ошибка ввода!\n");
        fclose(input);
        return 0;
    }
    double *mas = (double *) malloc(sizeof(double )*  m*n);
    int *mas_sr_arifm = (int *) malloc(sizeof(int)*m);
    for (int i = 0; i < n*m; i++){
        if (fscanf(input, "%lf", &mas[i]) == 0){
            printf("Ошибка ввода!\n");
            free(mas);
        }
    }

    for (int i = 0; i < m; i++){
        mas_sr_arifm[i] = find(&mas[i*n], n, &error);
        if (error == 1){
            free(mas);
            free(mas_sr_arifm);
            fclose(input);
        }
    }
    min = mas_sr_arifm[0];
    min_stroka = 0;
    for (int i = 0; i < m; i++){
        if (mas_sr_arifm[i] < min) {
            min = mas_sr_arifm[i];
            min_stroka = i;
        }
    }

    printf("%d\n", min_stroka);
    if (preobr(mas, min_stroka, m, n) != 0){
        free(mas);
        free(mas_sr_arifm);
        fclose(input);
        printf("Среднее аррифметическое одной из строк = 0!\n");
    }

    for(int i = 0; i < m; i ++) {
        for (int j = 0; j < n; j++){
            printf("%lf ", mas[i*n + j]);
        }
        printf("\n");
    }
    free(mas);
    free(mas_sr_arifm);
    fclose(input);
    return 0;
}
