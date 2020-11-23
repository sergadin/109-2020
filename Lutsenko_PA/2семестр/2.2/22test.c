#include <stdio.h>
#include <math.h>
#include "22.h"
#define e 2,71828
double f1 (double a);
double f2 (double a);
double f3 (double a);
double f4 (double a);
void AutoTest(void);



int main (void)


{

    double n [] = {10000,100, 100, 100};
    double  answ [] = {1.333333, 0.778238, 0.583333 , 2.925303};
    double x1 [] = {1, 0, -1, -1 };
    double x2 [] = {3, 1.5, 0, 1 };

    RRFUN f[] = {f1, f2, f3 , f4};
    
    double eps;
    double delta;
    for (int i=0 ;i<4 ;i++)
              {
            eps = fabs ( sum(x1[i], x2[i], n[i], f[i] ) - sum(x1[i], x2[i], n[i]/2, f[i] ) ) / 3;
            

	    
	          printf("\nright anwer = %10.6f",answ[i]); 
                  printf("\nyour answer = %10.6f",sum(x1[i], x2[i], n[i], f[i]) );
                  
                  printf("\nПогрешность по правилу Рунга = %10.6f",eps );
                  

              }
}




double f1 (double a)
{
	return  -(a-1)*(a-3);
}

double f2 (double a)
{
        return sin(pow(a,2));
}

double f3 (double a)
{
        return  pow(a,3) + pow(a,2) + a + 1;
}

double f4 (double a)
{
        return expf(pow(a,2)) ;
}

















