#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ftw.h>

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
 * Программу следует вызывать не менее чем с тремя дополнительными параметрами:
 * argv[1]: имя первого каталога;
 * argv[2]: имя второго каталога;
 * argv[3]: имя выходного файла.
 *
 * В случае, если передано меньше параметров, или если они некорректны 
 * (выходной файл невозможно открыть на запись или какой-либо каталог не находится), 
 * показывается сообщение об ошибке.
 */

int main(int argc, char **argv) {
	FILE *output;

	if (argc < 4) {
		fprintf(stderr, "The program hasn't got all the parameters\n");
		return -1;
	}

	if ((output = fopen(argv[3], "w")) == NULL) {
		fprintf(stderr, "Can't open %s\n", argv[3]);
		return -1;
	}

	curr_catalog = &files1;
	curr_len = &len1;
	curr_actual_len = &actual_len1;

	if (ftw(argv[1], fn, NOPENFD) != 0) {
		fprintf(stderr, "Something went wrong...\n");
		fclose(output);
		return -1;
	}

	for (int k = 0; k < *curr_actual_len; k++) {

	}

	curr_catalog = &files2;
	curr_len = &len2;
	curr_actual_len = &actual_len2;

	if (ftw(argv[2], fn, NOPENFD) != 0) {
		fprintf(stderr, "Something went wrong...\n");
		for (int i = 0; i < actual_len1; i++) {
			free(files1[i]);
		}
		fclose(output);
		return -1;
	}

	print_sym_difference(output, files1, argv[1], actual_len1, files2, argv[2], actual_len2);

	for (int i = 0; i < actual_len1; i++) {
		free(files1[i]);
	}

	for (int i = 0; i < actual_len2; i++) {
		free(files2[i]);
	}
	free(files1);
	free(files2);

	fclose(output);
	return 0;
}
