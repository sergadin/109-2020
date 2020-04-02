#include"iostream"
using namespace std;

class klin
{
	private:
		int n;
		double *x;
		double *y;
	public:
		klin(int dlin, double *a, double *b)
		{
			n = dlin;
			x = (double*) malloc(n *sizeof(double));
			y = (double*) malloc(n *sizeof(double));
			for(int i = 0; i < n; i++)
			{
				x[i] = a[i];
				y[i] = b[i];
			}
		}
		double interpolation(double x0)
		{
			double y0 = 0;
			return y0;
		}
};
