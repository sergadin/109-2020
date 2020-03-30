#include <iostream>
#include <cmath>
#include <cstdlib>

#include "interpolation.h"
#include "umath.h"

Point::Point(double x, double y) {
	this -> x = x;
	this -> y = y;
}

double Point::getX() {
	return this -> x;
}

double Point::getY() {
	return this -> y;
}

int Point::compare(const void *a, const void *b) {
	Point *A = (Point *)a;
	Point *B = (Point *)b;

	return compareDoubles(A -> x, B -> x, EPS);
}

Interpolation::Interpolation(Point *pts, int n, double precision, Status *s) {
	int i, j;

	this -> points = (Point *)malloc(n * sizeof(Point));
	this -> precision = precision;
	this -> n = n;
	*s = OK;

	if (n < 2) {
                *s = NOT_ENOUGH_DATA;
        } else {
		start = pts[0].getX();
        	end = pts[0].getX();

        	for (i = 0; i < n; i++) {
                	(this -> points)[i] = pts[i];

                	if (pts[i].getX() < start) start = pts[i].getX();
	                if (pts[i].getX() > end) end = pts[i].getX();
	        }

        	qsort(this -> points, n, sizeof(Point), Point::compare);

        	for (j = 0; j < n - 1; j++) {
                	if (compareDoubles((this -> points)[j].getX(), (this -> points)[j + 1].getX(), EPS) == 0) {
                        	*s = NOT_A_FUNCTION;
                	}
        	}
	}
}

double Interpolation::Lagrange(double x, Status *s) {
	int i, j;
	double value = 0, product;
	*s = OK;

	if ((x > this -> end) || (x < this -> start)) {
		*s = OUTSIDE_THE_SEGMENT;
		return 0;
	}

	for (i = 0; i < this -> n; i++) {
		product = 1;
		for (j = 0; j < this -> n; j++) {
			if (j == i) {
				continue;
			}
			product *= (x - (this -> points)[j].getX()) / ((this -> points)[i].getX() - (this -> points)[j].getX());
		}
		value += (this -> points)[i].getY() * product;
	}

	return value;
}

Interpolation::~Interpolation() {
	free(this -> points);
}
