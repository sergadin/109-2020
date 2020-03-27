#include<iostream>
using namespace std;

class CppInter
{
	private:
		int n = 6;
		double x[6];
		double y[6];
	public:
		void setPoint(int nn, double xx[6], double yy[6])
		{
			n = nn;
			x[6] = xx[6];
			y[6] = yy[6];
		}
		CppInter(int nn, double xx[6], double yy[6])
		{
			setPoint(nn, xx, yy);
		}
		void getPoint()
		{
			for(int i = 0; i < n; i++)
			{
				cout<<"x"<<x[i]<<"y"<<y[i]<<endl; 
			}
		}
		double newPoint(double x0)
		{
			double y0 = -1;
			double p = 1;
			for(int i = 0; i < n; i++)
			{
				if(x0 == x[i])
					return y[i];
			}
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
};
