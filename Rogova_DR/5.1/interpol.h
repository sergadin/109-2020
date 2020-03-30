#include"iostream"
using namespace std;

class CppInter
{
	private:
		int n;
		double * x;
		double * y;
	public:
		CppInter(int nn, double * xx, double * yy)
		{
			n = nn;
			x = (double *) malloc(n + 1);
			y = (double *) malloc(n + 1);
			for(int i = 0; i < n; i++)
			{
				x[i] = xx[i];
				y[i] = yy[i];
			}
		}
		double newPoint(double x0)
		{
			double y0 = -1;
			double p = 1;
			for(int i = 0; i < n; i ++)
			{
				y0 += p;
				p = 1;
				for(int j = 0; j < n; j++)
				{
					if(j != i)
						p = p*(x0 - x[j])/(x[i] - x[j]);
				}
				p = p*y[i];
			}
			return y0;

		}
		~CppInter()
		{
			free(x);
			free(y);
		}
};
