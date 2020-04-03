#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

class Appr
{
public:
	void approximation(double(*f)(double), double* a, int N)
	{
		double S1 = 0, S2 = 0, S3 = 0, S4 = 0;
		for (int i = 0; i < N; i++)
		{
			S1 += a[i] * a[i];
			S2 += a[i];
			S3 += f(a[i]) * a[i];
			S4 += f(a[i]);
		}
		k = (S3 * N - S2 * S4) / (S1 * N - S2 * S2);
		b = (S1 * S4 - S2 * S3) / (S1 * N - S2 * S2);
	}
	double return_k()
	{
		return k;
	}
	double return_b()
	{
		return b;
	}
private:
	double k;
	double b;
};

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
