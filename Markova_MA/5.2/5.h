#include"iostream"
#include"math.h"

using namespace std;

class c
{
	private:
		int n;
		double *x;
		double *y;	
	public:
		c(int long_, double *a, double *b)
		{	
			n = long_;
			x = (double*) malloc(n *sizeof(double));
			y = (double*) malloc(n *sizeof(double));


			for(int i = 0; i < n; i++)
			{
				x[i] = a[i];
				y[i] = b[i];
			}

		}
		double inter(double x0)
		{
			double y0 = 0;
			double tg = 0, a_0 = 0;
			if ((y == NULL) || (x == NULL))
			{
				throw -1;
			}
			for(int i = 1; i < n; i ++)
			{
				if ((x[i - 1] <= x0) && (x0 <= x[i]))
				{
					tg = (y[i] - y[i - 1])/(x[i] - x[i - 1]);
					a_0 = y[i - 1] - tg*x[i - 1];
					y0 = tg*x0 + a_0;
				}
			}
			return y0;
		}
		~c()
		{
			free(x);
			free(y);
		}
};