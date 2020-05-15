#include <stdio.h>

#include "getnames.h"

static void print_usage(char *program_name) {
	fprintf(stderr, "usage: %s dir1 dir2 output\n", program_name);
	fprintf(stderr, "dir1, dir2: directories to compare\n");
	fprintf(stderr, "output: file to print out results\n");
}

/*
 * Программу следует вызывать не менее чем с тремя дополнительными параметрами:
 * argv[1]: имя первого каталога;
 * argv[2]: имя второго каталога;
 * argv[3]: имя выходного файла.
 *
 * В случае, если передано меньше параметров, или если они некорректны 
 * (выходной файл невозможно открыть на запись или какой-либо каталог не находится), 
 * показывается сообщение об ошибке и выводится информация о корректном синтаксисе 
 * команды запуска программы.
 */

int main(int argc, char **argv) {
	FILE *output;
	int flag = 0;

	if ((argc < 4) || (argv[1] == "--help")) {
		print_usage(argv[0]);
		return -1;
	}

	if ((output = fopen(argv[3], "w")) == NULL) {
		fprintf(stderr, "Can't open %s\n", argv[3]);
		print_usage(argv[0]);
		return -1;
	}

	flag = get_names(output, argv[1], argv[2]);
	fclose(output);

	if (flag != 0) {
		fprintf(stderr, "Something went wrong\n");
		print_usage(argv[0]);
		return -1;
	}

	return 0;
}
