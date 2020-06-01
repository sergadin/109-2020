#include "iostream"
#include "math.h"
#include "5.hpp"


using namespace std;



int main (void)


{   double X=1;
   
    double x[] = {0, 2, 3, 4, 5};
    double x_1[] = {0.1, 2.1, 3.1, 4.1, 5.1};
    double true_answ [] = {5, 0.54, 2.718};
    
    double *y1 = (double *) malloc(5 * sizeof(double));
    double *y2 = (double *) malloc(5 * sizeof(double));
    double *y3= (double *) malloc(5 * sizeof(double));
    double *y1_1 = (double *) malloc(5 * sizeof(double));
    double *y2_1 = (double *) malloc(5 * sizeof(double));
    double *y3_1= (double *) malloc(5 * sizeof(double));
    
    double answ[] =(double *) malloc(3 * sizeof(double));;
   
    for (int i = 0 ; i <=4 ; i++)
    {
        y1[i] = x[i]*x[i] +4;
        y2[i] = cos (x[i]);
        y3[i] = expf(1/x[i]);
        
        y1_1[i] = x_1[i]*x_1[i] +4;
        y2_1[i] = cos (x_1[i]);
        y3_1[i] = expf(1/x_1[i]);
        

    }
    
    hermit p1(x,x_1,y1,y1_1,5);
    answ[0] = p1.Y(X);
    hermit p2(x,x_1,y2,y2_1,5);
    answ[1] = p2.Y(X);
    hermit p3(x,x_1,y3,y3_1,5);
    answ[2] = p3.Y(X);
    
    
 for (int i=0;i<3;i++)
              {
                  
                     std::cout<<"X = 1 "<<"answer: "<<answ[i]<<" true answer: "<<true_answ[i] <<endl;
                  
                
               }
    
    
    free(y1);
    free(y2);
    free(y3);
 
    free(y1_1);
    free(y2_1);
    free(y3_1);
    
    
    }



   





