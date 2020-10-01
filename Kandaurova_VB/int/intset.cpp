#include <iostream>
#include <string>
#include <cstdio>
#include <math.h>
#include "intset.h"

inte::inte(int l, int r) {
	n = 0;
	left = l;
	right = r;
}

inte::~inte() {
	if(n != 0)
		free(a);
	left = 0;
	right = 0;
	n = 0;
}

int inte::fleft() {
	return left;
}

int inte::fright() {
	return right;
}

int inte::fmax() {
	int max = left;
	if (n == 0)
		return NULL;
	for (int i = 0; i < n; i++)
		if (a[i] > max)
			max = a[i];
	return max;
}

int inte::fmin() {
	int min = left;
	if (n == 0)
		return NULL;
	for (int i = 0; i < n; i++)
		if (a[i] < min)
			min = a[i];
	return min;
}

int inte::check() const {
	if(n == 0)
		return 1;
	return 0;
}
