#include"iostream"
#include"math.h"

using namespace std;



class interpolution
{
	private:
		int n;
		double *x;
		double *y;	
	public:


		interpolution(int len, double *a, double *b) {	
			n = len;
			if ( n < 1 ) {
				throw -1;
			}
			
			x = (double*) malloc(n *sizeof(double));
			y = (double*) malloc(n *sizeof(double));

			for(int i = 0; i < n; i++) {
				x[i] = a[i];
				y[i] = b[i];
			}
		}

		double inter(double x0) {
			double y0 = 0;
			double k = 0, b = 0;
			for(int i = 1; i < n; i ++) {
				if ((x[i-1] <= x0) && (x0 <= x[i])) {
					k = ( y[i] - y[i-1] ) / ( x[i] - x[i-1] );
					b = y[i-1] - k * x[i-1];
					y0 = k * x0 + b;
				}
			}
			return y0;
		}
		~interpolution()
		{

			free(x);
			free(y);
		}
};


