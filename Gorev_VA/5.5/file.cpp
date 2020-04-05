#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "appr.h"

using namespace std;

double F1(double x)
{
	return 2.0 * x + 1;
}

double F2(double x)
{
	return x * x;
}

double F3(double x)
{
	return sin(x);
}

int main(void)
{
	Appr A;
	double* x;
	ErrorCode E;
	int N = 10;
	x = (double*)malloc(N * sizeof(double));
	for (int i = 0; i < N; i++)
	{
		x[i] = (double)i / (double)N;
	}
	cout << "approximation at 0, 0.1, ... , 0.9:\n";
	
	cout << "f(x) = x + 1:\n";
	A.approximation(F1, x, N, E);
	if (E = ERROR)
		cout << "Error of approximation\n";
	{
		cout << " calculated approximation: y = " << A.return_k() << " x + " << A.return_b() << "\n";
		cout << " actual approximation:     y = 2 x + 1\n";
		cout << " approximation value at x = 0.5: " << A.return_k() * 0.5 + A.return_b() << "\n";
		cout << " actual value at x = 0.5:        " << F1(0.5) << "\n";
	}
	
	cout << "f(x) = x^2:\n";
	A.approximation(F2, x, N, E);
	if (E = ERROR)
		cout << "Error of approximation\n";
	{
		cout << " calculated approximation: y = " << A.return_k() << " x + " << A.return_b() << "\n";
		cout << " actual approximation:     y = 0.9 x - 0.12\n";
		cout << " approximation value at x = 0.5: " << A.return_k() * 0.5 + A.return_b() << "\n";
		cout << " actual value at x = 0.5:        " << F2(0.5) << "\n";
	}
	
	cout << "f(x) = sin(x):\n";
	A.approximation(F3, x, N, E);
	if (E = ERROR)
		cout << "Error of approximation\n";
	{
		cout << " calculated approximation: y = " << A.return_k() << " x + " << A.return_b() << "\n";
		cout << " actual approximation:     y = 0.878649 x + 0.0218487\n";
		cout << " approximation value at x = 0.5: " << A.return_k() * 0.5 + A.return_b() << "\n";
		cout << " actual value at x = 0.5:        " << F3(0.5) << "\n";
	}
	
	cout << "Обновилась!\n;
	
	return 0;
}
