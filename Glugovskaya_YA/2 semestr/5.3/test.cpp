#include"interpol.h"
#include <math.h>
int main()
{
	int N = 6;
	double X;
    double *x = (double *) malloc(N * sizeof(double));
	double *y_line = (double *) malloc(N * sizeof(double)); //2*x+2
	double *y_parabola = (double *) malloc(N * sizeof(double)); //3*x*x+4*x+1
	double *y_sin = (double *) malloc(N * sizeof(double)); //sin(x)
	double x_points[] = {-1.5, -0.5, 0, 1, 1.5, 3};
	double X0 = 0.5;
	double Y0[] = {0, 0, 0};
	double CorAnswers[] = {3, 3.75, 0.479};
	
	
	for(int i = 0; i < N; i++)
	{
		X = x_points[i];
		y_line[i] = 2*X+2;
		y_parabola[i] = 3*X*X+4*X+1;
		y_sin[i] = sin(X);
	}
    PicQuadratic line(N, x_points, y_line);
	Y0[0] = line.solve(X0);

	PicQuadratic parabola(N, x_points, y_parabola);
	Y0[1] = parabola.solve(X0);

	PicQuadratic sin(N, x_points, y_sin);
	Y0[2] = sin.solve(X0);

	for(int i = 0; i < 3; i++)
	{
		cout<<"X0: 0.5 "<<"  Y0: "<<Y0[i]<<"  Correct Y0: "<<CorAnswers[i]<<endl;
	}
	return 0;
}
