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
int curr_len1 = 0, curr_len2 = 0;

/*
 * fn1 и fn2 - колбэк-функции для ftw
 *
 * Параметры:
 * fpath: путь к файлу (или директории)
 * sb: указатель на структуру, содержащую основную информацию о файле
 * typeflag: целочисленное значение, обозначающее тип файла
 *
 * fn* динамически выделяют память для массива files*, если место под очередное имя файла закончилось,
 * и добавляют в этот массив новое имя, если ftw вызвала fn не для директории, а для файла.
 *
 * Возвращаемое значение: в случае ошибки (выделения памяти) - (-1), в остальных случаях - 0.
 */

static int fn1(const char *fpath, const struct stat *sb, int typeflag) {
	char *last_slash;

	if (typeflag == FTW_D) {
		return 0;
	}

	if (len1 == curr_len1) {
		if ((files1 = (char **)realloc(files1, (len1 + ARR_EXTENSION) * sizeof(char *))) == NULL) {
			return -1;
		}
		len1 += ARR_EXTENSION;
	}

	last_slash = strrchr(fpath, '/');

	if (last_slash != NULL) {
		if ((files1[curr_len1] = (char *)malloc((strlen(last_slash + 1) + 1) * sizeof(char))) == NULL) {
			return -1;
		}
		strcpy(files1[curr_len1], last_slash + 1);
	} else {
		if ((files1[curr_len1] = (char *)malloc((strlen(fpath) + 1) * sizeof(char))) == NULL) {
			return -1;
		}
		strcpy(files1[curr_len1], fpath);
	}

	curr_len1++;
	return 0;
}

static int fn2(const char *fpath, const struct stat *sb, int typeflag) {
	char *last_slash;

	if (typeflag == FTW_D) {
		return 0;
	}

	if (len2 == curr_len2) {
		if ((files2 = (char **)realloc(files2, (len2 + ARR_EXTENSION) * sizeof(char *))) == NULL) {
			return -1;
		}
		len2 += ARR_EXTENSION;
	}

	last_slash = strrchr(fpath, '/');

	if (last_slash != NULL) {
		if ((files2[curr_len2] = (char *)malloc((strlen(last_slash + 1) + 1) * sizeof(char))) == NULL) {
			return -1;
		}
		strcpy(files2[curr_len2], last_slash + 1);
	} else {
		if ((files2[curr_len2] = (char *)malloc((strlen(fpath) + 1) * sizeof(char))) == NULL) {
			return -1;
		}
		strcpy(files2[curr_len2], fpath);
	}

	curr_len2++;
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
	int flag1, flag2;

	if (argc < 4) {
		fprintf(stderr, "The program hasn't got all the parameters\n");
		return -1;
	}

	if ((output = fopen(argv[3], "w")) == NULL) {
		fprintf(stderr, "Can't open %s\n", argv[3]);
		return -1;
	}

	if (ftw(argv[1], fn1, NOPENFD) != 0) {
		fprintf(stderr, "Something went wrong...\n");
		fclose(output);
		return -1;
	}

	if (ftw(argv[2], fn2, NOPENFD) != 0) {
		fprintf(stderr, "Something went wrong...\n");
		for (int i = 0; i < curr_len1; i++) {
			free(files1[i]);
		}
		fclose(output);
		return -1;
	}

	print_sym_difference(output, files1, argv[1], curr_len1, files2, argv[2], curr_len2);

	for (int i = 0; i < curr_len1; i++) {
		free(files1[i]);
	}

	for (int i = 0; i < curr_len2; i++) {
		free(files2[i]);
	}
	free(files1);
	free(files2);

	fclose(output);
	return 0;
}
