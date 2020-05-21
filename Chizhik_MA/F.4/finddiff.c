#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ftw.h>

#include "finddiff.h"

#define NOPENFD 10
#define ARR_EXTENSION 10

static char **files1 = NULL;
static char **files2 = NULL;

static int len1 = 0, len2 = 0;
static int actual_len1 = 0, actual_len2 = 0;

static char ***curr_catalog;
static int *curr_len;
static int *curr_actual_len;

/*
 * fn - колбэк-функция для ftw
 *
 * Параметры:
 * fpath: путь к файлу (или директории)
 * sb: указатель на структуру, содержащую основную информацию о файле
 * typeflag: целочисленное значение, обозначающее тип файла
 *
 * fn динамически выделяет память для массива, находящегося по адресу curr_catalog, если 
 * место под очередное имя файла закончилось, и добавляют в этот массив новое имя, 
 * если ftw вызвала fn не для директории, а для файла.
 *
 * Возвращаемое значение: в случае ошибки (выделения памяти) - (-1), в остальных случаях - 0.
 */

static int fn(const char *fpath, const struct stat *sb, int typeflag) {
	char *last_slash, *filename;

	if (typeflag == FTW_D) {
		return 0;
	}

	if (*curr_len == *curr_actual_len) {
		if ((*curr_catalog = (char **)realloc(*curr_catalog, (*curr_len + ARR_EXTENSION) * sizeof(char *))) == NULL) {
			return -1;
		}
		*curr_len += ARR_EXTENSION;
	}

	last_slash = strrchr(fpath, '/');
	if (last_slash != NULL) {
		filename = last_slash + 1;
	} else {
		filename = (char *)fpath;
	}

	if (((*curr_catalog)[*curr_actual_len] = (char *)malloc((strlen(filename) + 1) * sizeof(char))) == NULL) {
		return -1;
	}
	strcpy((*curr_catalog)[*curr_actual_len], filename);

	(*curr_actual_len)++;
	return 0;
}

/*
 * Колбэк-функция для qsort: возвращает отрицательное значение, если str1 < str2,
 * 0, если str1 и str2 совпадают, и положительное значение, если str1 > str2 
 * (используется лексикографический порядок)
*/

static int compare_strings(const void *str1, const void *str2) {
	return strcmp(*(char **)str1, *(char **)str2);
}

/* 
 * Освобождение памяти, выделенной под массив имен
 *
 * Параметры:
 * arr: массив имен
 * len: длина массива
 *
 * Функция освобождает память, выделенную для строк в массиве и для самого массива.
 */

static void free_catalog_array(char **arr, int len) {
	if (len < 1) {
		return;
	}
	for (int i = 0; i < len; i++) {
		free(arr[i]);
	}
	free(arr);
}

/*
 * Освобождение всех ресурсов, динамически выделяемых в данном блоке программы
 *
 * Функция освобождает ресурсы, выделенные под массивы имен, существующих в двух сравниваемых директориях.
 */

static void free_allocated_resources() {
	free_catalog_array(files1, actual_len1);
	free_catalog_array(files2, actual_len2);
}

/* 
 * Вывод списка имен, присутствующих в первом массиве имен и отсутствующих во втором
 *
 * Параметры аналогичны функции print_sym_difference (нет только dir2_name).
 * Функция получает на вход два отсортированных массива имен и, проходя по первому из них, 
 * находит в нем имена, которых нет во втором массиве.
*/

static void print_difference(FILE *output, 
		char **dir1, const char *dir1_name, int dir1_len, 
		char **dir2, int dir2_len) {
	fprintf(output, "%s: ", dir1_name);
	int j = 0;
	for (int i = 0; i < dir1_len; i++) {
		unsigned int belongs = 0;

		if ((i > 0) && (strcmp(dir1[i], dir1[i-1]) == 0)) {
			continue;
		}

		while ((j < dir2_len) && !(strcmp(dir1[i], dir2[j]) < 0)) {
			if (strcmp(dir1[i], dir2[j]) == 0) {
				belongs = 1;
				break;
			}
			j++;
		}

		if (belongs == 0) {
			fprintf(output, "%s ", dir1[i]);
		}
	}
	fprintf(output, "\n");
}

/* 
 * Печать имен, присутствующих в одном массиве строк и отсутствующих в другом
 *
 * Параметры:
 * output: файл, куда будет напечатана полученная информация;
 * dir1: массив имен файлов первого каталога;
 * dir2: массив имен файлов второго каталога;
 *
 * dir1_name, dir2_name: имя 1-го и 2-го каталогов соответственно;
 * dir1_len, dir2_len: длины соответствующих им массивов.
 *
 * Функция для каждого массива имен поочередно находит элементы, содержащиеся в нем, 
 * но отсутствующие в другом массиве имен и выводит два списка (в алфавитном порядке) в output.
 */

static void print_sym_difference(FILE *output,
		char **dir1, const char *dir1_name, int dir1_len, 
		char **dir2, const char *dir2_name, int dir2_len) {
	qsort(dir1, (size_t)dir1_len, sizeof(char *), compare_strings);
	qsort(dir2, (size_t)dir2_len, sizeof(char *), compare_strings);

	print_difference(output, dir1, dir1_name, dir1_len, dir2, dir2_len);
	print_difference(output, dir2, dir2_name, dir2_len, dir1, dir1_len);
}

int find_dir_diff(FILE *output, const char *dir1_name, const char *dir2_name) {
	if ((output == NULL) || (dir1_name == NULL) || (dir2_name == NULL)) {
		return -1;
	}

	curr_catalog = &files1;
	curr_len = &len1;
	curr_actual_len = &actual_len1;

	if (ftw(dir1_name, fn, NOPENFD) != 0) {
		free_catalog_array(files1, actual_len1);
		return -1;
	}

	curr_catalog = &files2;
	curr_len = &len2;
	curr_actual_len = &actual_len2;

	if (ftw(dir2_name, fn, NOPENFD) != 0) {
		free_allocated_resources();
		return -1;
	}

	print_sym_difference(output, files1, dir1_name, actual_len1, files2, dir2_name, actual_len2);
	free_allocated_resources();
	return 0;
}
