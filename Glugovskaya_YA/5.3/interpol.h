#include"iostream"
using namespace std;

class PicQuadratic
{
	private:
		int n;
		double * x;
		double * y;
		
	public:
		PicQuadratic(int count, double *CoordX, double *CoordY)
		{
			n = count;
			x = (double *) malloc(count * sizeof(double));
			y = (double *) malloc(count * sizeof(double));
			for(int i = 0; i < count; i++)
			{
				x[i] = CoordX[i];
				y[i] = CoordY[i];
			}
		}
		
		double solve(double X0)
		{
			double Y0 = 0, X1, Y1, X2, Y2, X3, Y3;
			if ((y == NULL) || (x == NULL))
			{
				throw 0;
			}
			
			
			for(int i = 1; i < n; i ++)
			{
				if ((x[i-1] <= X0) && (X0 <= x[i]))
				{
					if (i == 1) {
						X1 = x[0];
						Y1 = y[0];
						X2 = x[1];
						Y2 = y[1];
						X3 = x[2];
						Y3 = y[2];
					}
					else {
						X1 = x[i-2];
						Y1 = y[i-2];
						X2 = x[i-1];
						Y2 = y[i-1];
						X3 = x[i];
						Y3 = y[i];
					}
					 
					if ((X1 == X2) || (X2 == X3) || (X3 == X1))
					{
						throw 0;
					}
					
					Y0 = Y1 + (Y1 - Y2) * (X0 - X1) / (X1 - X2);
					Y0 += (Y1 - Y2) * (X0 - X2) * (X0 - X1) / ((X1 - X2) * (X1 - X3));
					Y0 -= (Y2 - Y3) * (X0 - X2) * (X0 - X1) / ((X2 - X3) * (X1 - X3));
					
					return Y0;
				}
			}

		}
		~PicQuadratic()
		{
			free(x);
			free(y);
		}
};
