#include <iostream>
#include <cmath>
#include <string>

#include "interpolation.h"
#include "../lib/umath.h"

using namespace std;

static double sq(double x) {
	return x * x;
}

int main(void) {
	double x[] = {-10, 0, 10};
	double y[] = {100, 0, 100}; //We expect y = x^2

	double test_x[] = {-25, -3, 0, 1, 2.5, 4, 38};
	int x_len, y_len, i, j, n;
	double result;
	Point *pts;
	Interpolation *points;

	x_len = (int)(sizeof(x) / sizeof(double));
	y_len = (int)(sizeof(y) / sizeof(double));

	if (x_len != y_len) {
		cerr << "Input is incorrect, please check it" << endl;
		return -1;
	} else if (x_len == 0) {
		cerr << "Empty input" << endl;
		return -1;
	}

	n = (int)(sizeof(test_x) / sizeof(double));

	if (n == 0) {
		cerr << "Array with test abscissae is empty" << endl;
		return -1;
	}

	pts = (Point *)malloc(x_len * sizeof(Point));
	for (j = 0; j < x_len; j++) {
		pts[j] = Point(x[j], y[j]);
	}

	try {
		points = new Interpolation(pts, x_len, EPS);
	} catch (UserException &e) {
		cerr << "An error has happened:" << endl << e.message() << endl;
		
		free(pts);
                return -1;
	}

	for (i = 0; i < n; i++) {
		cout << endl << "Test " << (i + 1) << endl;

		try {
			result = points -> Lagrange(test_x[i]);
		} catch (UserException &e) {
			cerr << "An error has happened: " << endl << e.message() << endl;
			continue;
		}

		cout << "Interpolated value: " << result << endl;
		cout << "Expected: " << sq(test_x[i]) << endl;
		if (compareDoubles(sq(test_x[i]), result, EPS) == 0) {
			cout << "The difference is incosiderable" << endl;
		} else {
			cerr << "Something went wrong..." << endl;
			delete points;
			free(pts);
			return -2;
		}
	}

	cout << "So, all the tests have been passed successfully. The program's output is correct" << endl;
	delete points;
	free(pts);	
	return 0;
}
