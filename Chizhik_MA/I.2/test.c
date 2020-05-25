#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../lib/umath.h"
#include "../2.3/simpson.h"

#include "solve.h"

#define EPS 1e-6

/*
 * Печать информации об использовании программы
 *
 * Параметры:
 * program_name: ./имя_исполняемого_файла
 *
 * Функция выводит в поток stderr информацию о том, как правильно вызывать данную программу.
 *
 */

static void print_usage(const char *program_name) {
	fprintf(stderr, "usage: %s alpha\n", program_name);
	fprintf(stderr, "alpha: value of the variable alpha in the equation\n");
}

/*
 * Программу следует вызывать по меньшей мере с одним дополнительным параметром:
 * argv[1]: значение alpha.
 *
 * В случае, если никакие параметры не переданы, показывается сообщение об ошибке 
 * и выводится информация о корректном синтаксисе команды запуска программы.
 *
 */

int main(int argc, char **argv) {
	double root, alpha, integral, c;
	double min_x = -M_PI/2;
	double max_x = M_PI/2;
	RootStatus r_s;
	IntStatus i_s;

	if (argc > 1) {
		alpha = atof(argv[1]);
	} else {
		print_usage(argv[0]);
		return -1;
	}

	root = solve_equation(1 + 0.1 * alpha, min_x, max_x, EPS, &r_s);
	if (r_s == OK_ROOT) {
		fprintf(stdout, "Root of the equation \nintegral of dt/(sqrt(1 + pow(t, 4))) = 1 + (%lf)\nis %lf\n", 0.1 * alpha, tan(root));
	} else {
		fprintf(stdout, "The equation \nintegral of dt/(sqrt(1 + pow(t, 4))) = 1 + (%lf) \ndoesn't have a root or the program can't find it\n", 0.1 * alpha);
	}

	integral = simpson_integral(f, 0, tan(root), EPS, &i_s);
	c = 1 + 0.1 * alpha;
	if ((i_s == OK_INT) && (r_s == OK_ROOT)) {
		fprintf(stdout, "Computed root: %lf\n", tan(root));
		fprintf(stdout, "Integral from 0 to %lf: %lf\n", tan(root), integral);
		fprintf(stdout, "1 + 0.1 * alpha = %lf\n", c);
		if (compareDoubles(c, integral, EPS * 3) == 0) {
			fprintf(stdout, "The difference's almost unnoticeable\n");
		} else {
			fprintf(stderr, "We're sorry, something went wrong\n");
			return -1;
		}
	}
	return 0;
}
