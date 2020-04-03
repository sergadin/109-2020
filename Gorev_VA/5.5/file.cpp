#include <iostream>
#include <cmath>
#include <stdlib.h>

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
	double* a, b;
	int N = 10;
	a = (double*)malloc(N * sizeof(double));
	for (int i = 0; i < N; i++)
	{
		a[i] = (double)i / (double)N;
	}
	cout << "approximation at 0, 0.1, ... , 0.9:\n";
	
	cout << "f(x) = x + 1:\n";
	cout << " calculated approximation: ";
	A.approximation(F1, a, N);
	cout << "y = " << A.return_k() << " x + " << A.return_b() << "\n";
	cout << " actual approximation:     ";
	cout << "y = 2 x + 1\n";
	
	cout << "f(x) = x^2:\n";
	cout << " calculated approximation: ";
	A.approximation(F2, a, N);
	cout << "y = " << A.return_k() << " x + " << A.return_b() << "\n";
	cout << " actual approximation:     ";
	cout << "y = 0.9 x - 0.12\n";
	
	cout << "f(x) = sin(x):\n";
	cout << " calculated approximation: ";
	A.approximation(F3, a, N);
	cout << "y = " << A.return_k() << " x + " << A.return_b() << "\n";
	cout << " actual approximation:     ";
	cout << "y = 0.878649 x + 0.0218487\n";
	return 0;
}
