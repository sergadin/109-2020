#include "iostream"
#include "math.h"

using namespace std;

class approximation
{
	private:
		int n;
		int i;
		double *x;
		double *y;
	public:
		approximation (int N, double *A, double *B)
		{
			n = N;
			if (n < 2)
			{
				throw -1;
			}
			x = (double*) malloc (n * sizeof(double));
			y = (double*) malloc (n * sizeof(double));
			if ((x == NULL) || (y == NULL))
			{
				throw -1;
			}
			for (i = 0; i < n; i++)
			{
				x[i] = A[i];
				y[i] = B[i];
			}
		}
		double interpolation (double point)
		{
			int check = 0;
			double k;
			double b;
			double answer;
			for (i = 0; i < (n - 1); i++)
			{
				if (point == x[i])
				{
					answer = y[i];
					check = 1;
				}
				else if ((x[i] < point) && (point < x[i + 1]))
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
