#include"iostream"
#include"math.h"
#include"kuslin.h"

using namespace std;
      
int main()
{
        int n = 10; 
        double *x = (double*) malloc(n *sizeof(double));
        double *y1 = (double*) malloc(n *sizeof(double));
	double *y2 = (double*) malloc(n *sizeof(double));
        double x0 = 4.589;
        double y0[] = {0, 0};
	double c[] = {-24.49, -0.8174};
        for(int i = 0; i < n; i++)
        {
                x[i] = i;
                y1[i] = 0.125*x[i]*x[i]+5-7*x[i];
		y2[i] = 5*sin(x[i]+5);
        }
        klin func1(n, x, y1);
        y0[0] = func1.interpolation(x0);
	klin func2(n, x, y2);
        y0[1] = func2.interpolation(x0);
        for(int i = 0; i < 2; i++)
        {
		cout<<"Правильный ответ="<< c[i] <<endl;
                cout<<"Мой ответ="<< y0[i] <<endl;
        }
return 0;
}
