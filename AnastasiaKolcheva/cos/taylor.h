#ifndef __READFILE_H___
#ifndef _USE_MATH_DEFINES
#define __READFILE_H___
#define _USE_MATH_DEFINES

double taylorSin(double x, double epsilon);

double taylorCos(double x, double epsilon);

void test(double epsilon, const char* name, double (*taylor)(double, double), double (*library)(double));

#endif
#endif