#include"iostream"
#include"math.h"
using namespace std;

class Pribl
{
	private:
		int n;
		double *x;
		double *x1;
		double *y;
		double *y1;
	public:
		Pribl(int len, double *xx, double *xx1, double yy, double *yy1)
		{
			n = len;
			x = (double*) malloc(n *sizeof(double));
			x1 = (double*) malloc(n *sizeof(double));
			y = (double*) malloc(n *sizeof(double));
                        y1 = (double*) malloc(n *sizeof(double));

			if (n <= 0)
			{
				throw -1;
			}

			for(int i = 0; i < n; i++)
			{
				x[i] = xx[i];
				x1[i] = xx1[i];
				y[i] = yy[i];
				y1[i] = yy1[i];
			}

		}

		double interpol(double x0)
		{
			double y0, f_i_1, f_i;

			for(int i = 1; i < n; i++)
			{
				if ((x[i-1] <= x0) && (x0 <= x[i]))
				{
					f_i_1 = (y1[i-1]-y[i-1])/(x1[i-1]-x[i-1]);
					f_i = (y1[i]-y[i])/(x1[i]-x[i]);
					
					y0 = y[i-1] + (x0-x[i-1])*(f_i_1 + ((x0-x[i-1])*(f_i_1-(y[i-1]-y[i])/(x[i-1]-x[i])+(x0-x[i])*
								(f_i_1-2*(y[i-1]-y[i])/(x[i-1]-x[i])+f_i)/(x[i-1]-x[i])))/(x[i-1]-x[i]));
				        
				}
			}

			return y0;
		}

		~Pribl()
		{

			free(x);
			free(x1);
			free(y);
			free(y1);
		}
};


