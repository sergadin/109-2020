#include <iostream>
#include "math.h"
#include "interpolation.h"

using namespace std;

int main()
{
	try
	{
    // Тест №1
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
			y[i] = log(sin(x[i])) * sqrt(x[i]);
    }
    ea = log(sin(point)) * sqrt(point);
		approximation test1(n, x, y);
		ca = approximation.interpolation(point);
    cout << "Test № 1: OK" << endl;
		cout << "Calculated answer = " << ca << " | " ;
		cout << "Exact answer = " << ea << endl;
		}
		free(y);
	}
	catch(...)
	{
		cout << "Test № 1: LOSS " << endl;
	}
	return 0;
}
