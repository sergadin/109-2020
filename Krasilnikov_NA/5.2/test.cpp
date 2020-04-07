#include <iostream>
#include "math.h"
#include "interpolation.h"

using namespace std;

int main()
{
	try
	{
		// Тест № 1
		int n = 10;
		double x1[n] = {1.59, 1.87, 2.51, 3.43, 4.88, 7.22, 8, 8.04, 8.8, 9.49};
		double point = 2.43;
		double ca; //calculated_answer
		double ea; //exact_answer
		double *y = (double*) malloc(n *sizeof(double));
		if (y == NULL)
		{
			throw -1;
		}
		for(int i = 0; i < n; i++)
		{
			y[i] = log(sin(x1[i])) * sqrt(x1[i]);
		}
		ea = log(sin(point)) * sqrt(point);
		approximation test1(n, x1, y);
		ca = test1.interpolation(point);
		cout << "Test № 1: OK" << endl;
		cout << "Calculated answer = " << ca << " | " ;
		cout << "Exact answer = " << ea << endl;
		free(y);
	}
	catch(...)
	{
		cout << "Test № 1: LOSS " << endl;
	}
  try
	{
		// Тест № 2
		int n = 5;
		double x2[n] = {2.61, 3.83, 5.59, 6.64, 7.85};
		double point = 4.41;
		double ca;
		double ea;
		double *y = (double*) malloc(n *sizeof(double));
		if (y == NULL)
		{
			throw -1;
		}
		for(int i = 0; i < n; i++)
		{
			y[i] = x2[i] * x2[i] + 4;
		}
		ea = point * point + 4;
		approximation test2(n, x2, y);
		ca = test2.interpolation(point);
		cout << "Test № 2: OK" << endl;
		cout << "Calculated answer = " << ca << " | " ;
		cout << "Exact answer = " << ea << endl;
		free(y);
	}
	catch(...)
	{
		cout << "Test № 2: LOSS " << endl;
	}
  try
	{
		// Тест № 3
		int n = 7;
		double x3[n] = {1.03, 2.12, 2.96, 3.91, 4.73, 5.65, 6.83};
		double point = 6.57;
		double ca;
		double ea;
		double *y = (double*) malloc(n *sizeof(double));
		if (y == NULL)
		{
			throw -1;
		}
		for(int i = 0; i < n; i++)
		{
			y[i] = 6 * x3[i] * x3[i] * x3[i] + 3 * x3[i] * x3[i] + x3[i] + 4;
		}
		ea = 6 * point * point * point +  3 * point * point + point + 4;
		approximation test3(n, x3, y);
		ca = test3.interpolation(point);
		cout << "Test № 2: OK" << endl;
		cout << "Calculated answer = " << ca << " | " ;
		cout << "Exact answer = " << ea << endl;
		free(y);
	}
	catch(...)
	{
		cout << "Test № 2: LOSS " << endl;
	}
	return 0;
}
