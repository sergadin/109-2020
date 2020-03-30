#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

#include "interpolation.h"
#include "umath.h"

using namespace std;

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

Interpolation::Interpolation(Point *pts, int n, double precision) {
	int i, j;

	this -> points = (Point *)malloc(n * sizeof(Point));
	this -> precision = precision;
	this -> n = n;

	if (n < 2) {
                throw UserException(3, "The amount of points is not enough to compute anything");
        }
		
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
                       	throw new UserException(1, "Two points have equal abscissae");
               	}
       	}
}

double Interpolation::Lagrange(double x) {
	int i, j;
	double value = 0, product;

	if ((x > this -> end) || (x < this -> start)) {
		throw UserException(2, "This abscissa doesn't have an interpolated value");
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

UserException::UserException(int code, string message) : code_(code), message_(message) {}

string UserException::message() const {
	return this -> message_;
}

int UserException::code() const {
	return this -> code_;
}
