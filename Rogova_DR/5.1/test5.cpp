#include"interpol.h"


int main()
{
	double x[] = {1, 3, 4, 5, 6, 7};
	double yline[] = {1, 3, 4, 5, 6, 7};
	double ysqr[] = {1, 9, 16, 25, 36, 49};
	double yzer[] = {0, 0, 0, 0, 0, 0};
	double truan[] = {2, 4, 0};	
	double x0 = 2;
	double y0[] = {0, 0, 0};
	int n = 6;
	CppInter line(n, x, yline);
	y0[0] = line.newPoint(x0);

	CppInter sqr(n, x, ysqr);
	y0[1] = sqr.newPoint(x0);

	CppInter zer(n, x, yzer);
	y0[2] = zer.newPoint(x0);

	for(int i = 0; i < 3; i++)
	{
		cout<<"x0=2"<<"my:"<<y0[i]<<"true:"<<truan[i]<<endl;
	}
	return 0;
}
