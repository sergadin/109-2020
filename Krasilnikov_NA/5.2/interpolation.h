#include "iostream"
#include "math.h"

using namespace std;

class approximation
{
	private:
		int _n;
		double *x;
		double *y;
	public:
		approximation (int N, double *A, double *B)
		{
      int i;
			_n = N;
			if _(n < 2)
			{
				throw -1;
			}
			x = (double*) malloc (_n * sizeof(double));
			y = (double*) malloc (_n * sizeof(double));
			if ((x == NULL) || (y == NULL))
			{
				throw -1;
			}
			for (i = 0; i < _n; i++)
			{
				x[i] = A[i];
				y[i] = B[i];
			}
		}
		double interpolation (double point)
		{
    	int i;
			int check = 0;
			double k;
			double b;
			double answer;
			for (i = 0; i < (_n - 1); i++)
			{
				if ((x[i] < point) && (point < x[i + 1]))
				{
					k = (y[i + 1] - y[i])/(x[i  + 1] - x[i]);
					b = y[i + 1] - k * x[i + 1];
					answer = k * point + b;
					check = 1;
				}
			}
			if (check == 0)
			{
				throw -1;
			}
			return answer;
		}
		~approximation()
		{
			free(x);
			free(y);
		}
};
