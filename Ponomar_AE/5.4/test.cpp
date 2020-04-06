#include"iostream"
#include"math.h"
#include "pribl.h"

using namespace std;

int main()
{
	try
	{
		int n = 8;
		double x[] = {1, 2.5, 3, 3.5, 4, 4.5, 5, 6};
		double x1[] = {1.05, 2.55, 3.05, 3.55, 4.05, 4.55, 5.05, 6.05};
		double x0 = 3.8;
		double y0[] = {0, 0, 0};
		double true_answer[] = {3.8, 14.44, 0.066};

		double *linear = (double *) malloc(n * sizeof(double));
		double *square = (double *) malloc(n * sizeof(double));
		double *sinus = (double *) malloc(n * sizeof(double));
		double *linear1 = (double *) malloc(n * sizeof(double));
                double *square1 = (double *) malloc(n * sizeof(double));
                double *sinus1 = (double *) malloc(n * sizeof(double));

		if ((x1 == NULL) || (linear == NULL) || ((square) == NULL) || ((sinus) == NULL))
		{
			throw 123;
		}

		for(int i = 0; i < n; i++)
		{
			linear[i] = x[i];
			square[i] = x[i] * x[i];
			sinus[i] = sin(x[i]);
		     	linear1[i] = x1[i];
                        square1[i] = x1[i] * x1[i];
                        sinus1[i] = sin(x1[i]);
		}

		Pribl line(n, x, x1, linear, linear1);
		y0[0] = line.interpol(x0);

		Pribl sqr(n, x, x1, square, square1);
		y0[1] = sqr.interpol(x0);

		Pribl sin(n, x, x1, sinus, sinus1);
		y0[2] = sin.interpol(x0);

		for(int i = 0; i < 3; i++)
		{
			cout<<"x0 = 3.8 "<<"real: "<<y0[i]<<" true: "<<true_answer[i] <<endl;
		}

		free(linear);
		free(square);
		free(sinus);
		free(linear1);
                free(square1);
                free(sinus1);

	}

	catch(int code)
	{
		cout<<"error "<<endl;
	} 

	return 0;
}

