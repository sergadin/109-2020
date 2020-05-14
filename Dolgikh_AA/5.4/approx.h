#include <iostream>
#include "math.h"
using namespace std;

class Approx
{
	private:
		int n;
		double *z;
		double *yz;
		double *y1z;
	public:
		Approx(int N, double *x, double *y, double *y1)
		{
			n = N;
			z = (double *)malloc(2 * n * sizeof(double));
			yz = (double *)malloc(2 * n * sizeof(double));
			y1z = (double *)malloc(2 * n * sizeof(double));

			
			for(int i = 0; i < n; i++)
			{
				z[2 * i] = z[2 * i + 1] = x[i];
				yz[2 * i] = yz[2 * i + 1] = y[i];
				y1z[2 * i] = y1z[2 * i + 1] = y1[i];
			}
		}
		//Функция для посчитать разделенную разность
		double razdraz(int k, int l)
		{
			if(k == l)
				return yz[k];
			if(l - k == 1 && k%2 == 0)
				return y1z[k];
			else
				return (razdraz(k + 1, l) - razdraz(k, l - 1)) / (z[l] - z[k]);
		}
		double Hermite(double x0)
		{
			double res = yz[0];
			double s = 1;
			for(int i = 1; i < 2 * n; i++)
			{
				s = razdraz(0, i);
				for(int j = 0; j < i; j++)
				{
					s *= (x0 - z[j]);
				}
				res += s;
			}
			return res;
		}
		~Approx()
		{
			free(z);
			free(yz);
			free(y1z);
		}
};
