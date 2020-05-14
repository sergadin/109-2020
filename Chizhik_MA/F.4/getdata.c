#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ftw.h>

#include "getdata.h"
#include "printdiff.h"

#define NOPENFD 10
#define ARR_EXTENSION 10

char **files1 = NULL;
char **files2 = NULL;

int len1 = 0, len2 = 0;
int actual_len1 = 0, actual_len2 = 0;

char ***curr_catalog;
int *curr_len;
int *curr_actual_len;

/*
 * fn - колбэк-функция для ftw
 *
 * Параметры:
 * fpath: путь к файлу (или директории)
 * sb: указатель на структуру, содержащую основную информацию о файле
 * typeflag: целочисленное значение, обозначающее тип файла
 *
 * fn динамически выделяет память для массива, находящегося по адресу curr_catalog, если 
 * место под очередное имя файла закончилось, и добавляют в этот массив новое имя 
 * (без пути к файлу, только его имя; поэтому два разных файла с одним и тем же именем будут 
 * отождествлены), если ftw вызвала fn не для директории, а для файла.
 *
 * Возвращаемое значение: в случае ошибки (выделения памяти) - (-1), в остальных случаях - 0.
 */

static int fn(const char *fpath, const struct stat *sb, int typeflag) {
	char *last_slash;

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
		if (((*curr_catalog)[*curr_actual_len] = (char *)malloc((strlen(last_slash + 1) + 1) * sizeof(char))) == NULL) {
			return -1;
		}
		strcpy((*curr_catalog)[*curr_actual_len], last_slash + 1);
	} else {
		if (((*curr_catalog)[*curr_actual_len] = (char *)malloc((strlen(fpath) + 1) * sizeof(char))) == NULL) {
			return -1;
		}
		strcpy((*curr_catalog)[*curr_actual_len], fpath);
	}

	(*curr_actual_len)++;
	return 0;
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

int get_data(FILE *output, char *dir1_name, char *dir2_name) {
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
