#include "libs.h"

/**
** Считывание строки
**
** Параметры: FILE *in: входной файл.
**
** Функция считывает строку из файла, выделяя необходимое количество памяти.
**
*/
char *read_string(FILE *in) {
    char buf[1024];
    char *s = fgets(buf, 1024, in);
    if(s) {
        int len = strlen(s);
        int tmp = 0;
		int past_len = 0;
        char *res = malloc(len+1);
        while(s) {
            strcpy(res+past_len, s);
            if(s[strlen(s)-1] == '\n') break;
            s = fgets(buf, 1024, in);
            if (s) {
                tmp = strlen(s);
                past_len = len;
                len += tmp;
                res = realloc(res, len+1);
            }
        } 
        if(res[strlen(res)-1] == '\n'){
            res[strlen(res)-1] = '\0';
        }
        return res;
    } 
    return NULL;
}

/**
** Печать матрицы размера n на m
**
** Параметры:
** char **matrix: матрица из слов;
** int n: количество строк;
** int m: количество столбцов.
**
** Функция печатает матрицу, представленную одномерным массивом.
**
*/
void print_matrix(char **matrix, int n, int m, FILE * out) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++){
            fprintf(out, "%s\n", matrix[i*m + j]);
        }
        //printf("\n");
    }
}

/**
** Считывание матрицы из файла
**
** Параметры:
** char **matrix: матрица из слов;
** FILE *inp: входной файл;
** int n: количество элементов матрицы.
**
** Функция считывает из файла элементы матрицы.
** Если количество строк в файле меньше, чем количество элементов матрицы,
** то оставшиеся элемены матрицы заполняются пустыми строками.
**
*/
void read_matrix(char **matrix, FILE *inp, int n) {
    for(int i = 0; i < n; i++) {
        matrix[i] = read_string(inp);
        if (matrix[i] == NULL) {
            matrix[i] = malloc(1);
            matrix[i][0] = '\0';
        }
    }
}

/** Функция поиска строки k
**
** Параметры:
** char **matrix: матрица слов;
** int n: количество строк;
** int m: количество столбцов.
**
** Функция ищет строку k матрицы A, такую что обращенное слово R(W(k))
** совпадает с некоторым из слов W(i)
** 
** Метод: посимвольно сравниваем строки R(W(k)) и W(i)
** Возращаемое значение: в случае успеха номер строки k, иначе - (-1).
** 
*/
int search(char **matrix, int n, int m) {
    for(int k = 0; k < n; k++){
        int k_len = 0;
        for(int i = 0; i < m; i++) {
            k_len += strlen(matrix[k*m + i]);
        }
        for(int j = 0; j < n; j++) {
            int tmp_len = 0;
            for(int i = 0; i < m; i++) {
                tmp_len += strlen(matrix[j*m + i]);
            }
            if (k_len == tmp_len) {
                int flag = 1;
                int k_i = m - 1, k_j = strlen(matrix[k*m + k_i]) - 1;
                int tmp_i = 0, tmp_j = 0;
                while(1) {
                    if(matrix[k*m + k_i][k_j] != matrix[j*m + tmp_i][tmp_j]){
                        flag = 0;
                        break;
                    }
                    k_j--;
                    if(k_j < 0) {
                        k_i--;
                        if(k_i < 0) break;
                        k_j = strlen(matrix[k*m + k_i]) - 1;
                    }
                    tmp_j++;
                    if(tmp_j >= strlen(matrix[j*m + tmp_i])) {
                        tmp_i++;
                        if(tmp_i >= m) break;
                        tmp_j = 0;
                    }
                }
                //printf("%d", flag);
                if(flag) return k;
            }
        }
    }
    return -1;
}

/** Функция сложения строк
**
** Параметры:
** char **matrix: матрица слов;
** int n: количество строк;
** int m: количество столбцов;
** int k: номер найденной строки.
**
** Сложение найденной строки k и строки p (для каждого q = 0, ..., m-1) 
** происходит вычеркиванием из слова A_pq букв слова A_kq.
** 
** Метод: находим символ в строке с помощью функции strchr из библиотеки <string.h>,
** после чего сдвигаем все символы после найденного на 1 влево, повторяем до тех пор, 
** пока не уберем все символы из строки, совпадающие с искомым
**
*/
void sum(char **matrix, int n, int m, int k){
    if(k == -1) return;
    for (int i = 0; i < n; i++) {
        if(i == k) continue; 
        for (int j = 0; j < m; j++) {
            int len = strlen(matrix[k*m + j]);
            for (int t = 0; t < len; t++) {
                char c = matrix[k*m + j][t];
                char *tmp;
                while((tmp = strchr(matrix[i*m + j], c)) != NULL) {
                    int tmp_len = strlen(tmp);
                    for(int z = 1; z <= tmp_len; z++){
                        tmp[z-1] = tmp[z];
                    }
                }
            }
        }
    }
}
