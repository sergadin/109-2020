#include "iostream"
#include "math.h"
#include "5.hpp"


using namespace std;



int main (void)


{   double *y1 = (double *)malloc(4 * sizeof (double)); //значения
    double *y2 = (double *)malloc(4 * sizeof (double));
    double *y3 = (double *)malloc(4 * sizeof (double));
    double *y4 = (double *)malloc(4 * sizeof (double));
    
    double *z1 = (double *)malloc(4 * sizeof (double)); //  первые производные
    double *z2 = (double *)malloc(4 * sizeof (double));
    double *z3 = (double *)malloc(4 * sizeof (double));
    double *z4 = (double *)malloc(4 * sizeof (double));

    double *answ = (double *)malloc(4 * sizeof (double));
    
    double e [] = {0,1,0,001, 0,001, 0,0001};
    double true_answ [] = {4, -1, 1 , 1.284025};
    double x1 [] = {0.1, 0.2, 0.3, 0.4 };
    double x2 [] = {0.01, 0.02, 0.03, 0.04 };
    double x3 [] = {0.1, 0.2, 0.3, 0.4 };
    double x4 [] = {0.01, 0.02, 0.03, 0.04 };
     
    double h=0.1;
    double X=1;

    int i;
    for (i = 0 ; 1 <=4 ; i++)
    {
        y1[i] = x1[i]*x1[i] +4;
        y2[i] = cos (x2[i]);
        y3[i] = pow(x3[i],3) - pow(x3[i],2) + x3[i] + 1;
        y4[i] = expf(1/x4[i]);
        
        z1[i] = ((x1[i]*x1[i] +4) - (x1[i]-h)*(x1[i]-h) +4 ) / h;
        z2[i] = (cos (x2[i]) - cos (x2[i]-h)) / h;
        z3[i] = (pow(x3[i],3) - pow(x3[i],2) + x3[i] + 1) - ( pow(x3[i]-h,3) - pow(x3[i]-h,2) + x3[i]-h + 1) / h;
        z4[i] = (expf(1/x4[i])- expf(1/x4[i]-h)) / h;
        

    }
    
    hermit p1(x1,y1,z1,4);
    answ[0] = p1.Y(X);
    hermit p2(x2,y2,z2,4);
    answ[1] = p2.Y(X);
    hermit p3(x3,y3,z3,4);
    answ[2] = p3.Y(X);
    hermit p4(x4,y4,z4,4);
    answ[3] = p4.Y(X);
    
    




    for (int i=0;i<4;i++)
              {
                  if (fabs(answ[i] - true_answ[i])<e[i])
                  {
                      std::cout<<"OK";
                  }
                  else
                  {
                     std::cout<<"autotest failed";
                  }
               }
    
    
    free(y1);
    free(y2);
    free(y3);
    free(y4);
    free(z1);
    free(z2);
    free(z3);
    free(z4);
    
    
}





