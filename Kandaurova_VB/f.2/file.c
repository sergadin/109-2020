/*
    * Программа выводит имена файлов и их размеры из данного каталога и всех его подкаталогов
	*
    * Параметры:
    *   int argc: количество аргументов командной строки
    *   char *argv[]: массив аргументов командной строки
    *  
    * Количество аргументов командной строки может быть равно 1 или 2 
    * Первый аргумент командной строки - исполняемый файл
    * Если аргументаов 2, то второй аргумент - каталог, с которым работает программа
    * Если второй аргумент отсутствует, программа работает с текущим каталогом
	* Если количество аргументов командной строки больше 2, то все аргументы после второго игнорируются
	*
	* В результате работы программы на стандартный поток вывода будет напечатан список всех файлов и их размеры  
	* 
    * Метод:
    *   Для обхода дерева файлов, используется функция ftw из библиотеки <ftw.h>.
*/

#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define Max_len 30

char **s, **s_value = NULL;
intmax_t *size, *size_value = NULL;
int n = 0, max_len = 0;

static int fn(const char *fpath, const struct stat *sb, int flag);

/*
    * fn - колбэк-функция для ftw, вызываемая для всех файлов
    *
    * Параметры:
    *   const char *fpath: путь к файлу
    *   const struct *sb: указатель на структуру stat, содержащую основную информацию о файле
    *   int flag: целочисленное значение, обозначающее тип fpath
    *
    * Функция копирует в массив s название файла, а в массив size его размер
 */

void print(int k, int max);

/*
    * Функция выводит (max - k + 5)  пробелов на стандартный поток вывода
*/

static int fn(const char *fpath, const struct stat *sb, int flag) {
    if(flag == FTW_F) {
        n++;
        s = (char **) realloc (s_value, n * sizeof(char *));
        size = (intmax_t *) realloc (size_value, n * sizeof(intmax_t));
        s[n - 1] = malloc((strlen(fpath) + 1) * sizeof(char));
        strcpy(s[n - 1], fpath);
        size[n - 1] = (intmax_t) sb->st_size;
        s_value = s;
        size_value = size;
        if(strlen(s[n - 1]) > max_len)
            max_len = strlen(s[n - 1]);
    }
    return 0;
}

void print(int k, int max) {
    for(int i = 0; i < max - k + 4; i++)
        printf(" ");
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        if(ftw(".", fn, 20) == -1)  {
            printf("Не удалось обойти каталог\n");
            return -1;
        }
    }
    else {
        if(ftw(argv[1], fn, 20) == -1)  {
            printf("Не удалось обойти каталог\n");
            return -1;
        }
    }
    if(max_len > Max_len) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < strlen(s[i]); j++) {
                printf("%c", s[i][j]);
                if (j == Max_len - 1)
                    printf("     %jd", size[i]);
                if((j % Max_len == Max_len - 1) || (j == strlen(s[i]) - 1))
                    printf("\n");
            }
        }
    }
    else {
        for(int i = 0; i < n; i++) {
            printf("%s", s[i]);
            print(strlen(s[i]), max_len);
            printf("%jd\n", size[i]);
        }
    }
    for(int i = 0; i < n; i++) {
        free(s[i]);
    }
    free(s);
    free(size);
    return 0;
}
