#ifndef __READFILE_H___

#define __READFILE_H___

typedef double (*func)(double x);

double findMinimum(func f, double a, double b, double epsilon);

#endif