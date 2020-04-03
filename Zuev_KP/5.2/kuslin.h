#include"iostream"
#include"math.h"

using namespace std;

class klin
{
	public:
		
		double interpolation(double x0, int n, double *a, double *b)
		{
			double y0 = 0;
			double h = 0, k = 0;
			for(int i = 1; i < n; i ++)
			{
				if ((a[i-1]<=x0) && (x0<=a[i]))
				{
					h = (b[i]-b[i-1])/(a[i]-a[i-1]);
					k = b[i-1]-h*a[i-1];
					y0 = h*x0+k;
				}
			}
			return y0;
		}
};
