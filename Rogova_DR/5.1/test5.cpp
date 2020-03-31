#include"interpol.h"


int main()
{
	int n0 = 6;
       	double * x1 = (double *) malloc(n0*sizeof(double));
	double * yline = (double *) malloc(n0*sizeof(double));
	double * ysqr = (double *) malloc(n0*sizeof(double));
	double * yzer = (double *) malloc(n0* sizeof(double));
	double truan[] = {2, 4, 0};
	double x0 = 0.6;
	double y0[] = {0, 0, 0};
	for(int i = 0; i < n0; i++)
	{
		x1[i] = i;
		yline[i] = i;
		ysqr[i] = i*i;
		yzer[i] = 0;
	}
       	CppInter line(n0, x1, yline);
	y0[0] = line.newPoint(x0);

	CppInter sqr(n0, x1, ysqr);
	y0[1] = sqr.newPoint(x0);

	CppInter zer(n0, x1, yzer);
	y0[2] = zer.newPoint(x0);

	for(int i = 0; i < 3; i++)
	{
		cout<<"x0=2"<<"my:"<<y0[i]<<"true:"<<truan[i]<<endl;
	}
	return 0;
}
