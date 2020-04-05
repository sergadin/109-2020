#include"iostream"
#include"math.h"
#include"5.h"

using namespace std;

int main()
{
	try
	{	
		int n = 10; 
		double x[5] = {1, 2, 2.4, 3, 4, 5.6, 7, 8, 9, 10};
		double x0 = 6;
		double y0[2] = {0, 0};
		double true_ans[2] = {216, 5.93989};
		double *y1 = (double*) malloc(n *sizeof(double));
		double *y2 = (double*) malloc(n *sizeof(double));
		if ((y1 == NULL) || (y2 == NULL))
		{
			throw -1;
		}
		for(int i = 0; i < n; i++)
		{
			y1[i] = x[i]*x[i]*x[i];
			y2[i] = 5*cos(x[i])*cos(x[i]) + cos(x[i]);
		}
		c f1(n, x, y1);
		y0[0] = f1.inter(x0);
		c f2(n, x, y2);
		y0[1] = f2.inter(x0);
		for(int i = 0; i < 2; i++)
		{	
			cout<<"true answer = "<< true_ans[i] << endl;
			cout<<"my answer = "<< y0[i] << endl;
		}
		free(y1);
		free(y2);
	}
	catch(...)
	{
		cout << "error " << endl;
	}
	return 0;
}