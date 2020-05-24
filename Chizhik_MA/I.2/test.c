#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../lib/umath.h"
#include "../1.3/secant.h"
#include "../2.3/simpson.h"

#include "solve.h"

#define EPS 1e-6
static RootStatus r_s;
static IntStatus i_s;

static double f(double t) {
	return 1 / sqrt(1 + pow(t, 4));
}

/* Заменив f на f_imp, можно вместо рассмотрения всей числовой прямой
 * ограничиться рассмотрением отрезка [-PI/2, PI/2]
 */

static double f_imp(double z) {
	return 1 / sqrt(pow(cos(z), 4) + pow(sin(z), 4));
}

static double integral(double x) {
	return simpson_integral(f, 0, x, EPS, &i_s);
}

static double integral_imp(double x) {
	return simpson_integral(f_imp, 0, x, EPS, &i_s);
}

static void print_usage(const char *program_name) {
	fprintf(stderr, "usage: %s alpha\n", program_name);
	fprintf(stderr, "alpha: value of the variable alpha in the equation\n");
}

/*
 * Программу следует вызывать по меньшей мере с одним дополнительным параметром:
 * argv[1]: значение alpha.
 *
 * В случае, если параметры не переданы, показывается сообщение об ошибке 
 * и выводится информация о корректном синтаксисе команды запуска программы.
 *
 */

int main(int argc, char **argv) {
	int alpha;
	double min_x = -M_PI/2;
	double max_x = M_PI/2;

	if (argc >1) {
		alpha = atoi(argv[1]);
	} else {
		print_usage(argv[0]);
		return -1;
	}

	fprintf(stdout, "Integral of dz/(sqrt(pow(cos(z), 4) + pow(sin(z), 4))) from 0 to PI/2 equals to %lf\n", integral_imp(M_PI/2));
	fprintf(stdout, "Integral of dz/(sqrt(pow(cos(z), 4) + pow(sin(z), 4))) from 0 to -PI/2 equals to %lf\n", integral_imp(-M_PI/2));
	fprintf(stdout, "%d\n", atoi(argv[1]));
	return 0;
}
