#include "iostream"
#include "math.h"
#include "5.hpp"


using namespace std;



int main (void)

{
    double XX = 1;
    double h = 0.1;
    int n = 5;
    double x[] = {0, 1, 2, 3, 4};
    double true_answ [] = {5, 0.54, 0.5};
    
    double *y1 = new double[n];
    double *y2 = new double[n];
    double *y3 = new double[n];
    
    double *y1_1 = new double[n];
    double *y2_1 = new double[n];
    double *y3_1 = new double[n];
    
    double *answ = new double[3];
    
   
    for (int i = 0 ; i <n ; i++)
    {
        y1[i] = x[i]*x[i] + 4;
        y2[i] = cos (x[i]);
        y3[i] = x[i] - 0.5;
        
        y1_1[i] = ( (x[i]+h)*(x[i]+h) -  x[i]*x[i]  ) / h;
        y2_1[i] = (cos (x[i]+ h) - cos (x[i])) / h;
        y3_1[i] = ((x[i] - 0.5 + h)-(x[i] - 0.5)) / h;
        

    }
    
    hermit p1(x, y1,y1_1 ,n );
    answ[0] = p1.Y(XX);
    hermit p2(x ,y2 ,y2_1 ,n );
    answ[1] = p2.Y(XX);
    hermit p3(x ,y3 ,y3_1 ,n );
    answ[2] = p3.Y(XX);
    
    
        for (int i=0;i<3;i++)
           std::cout<<"X = 1 "<<"answer: "<<answ[i]<<" true answer: "<<true_answ[i] <<endl;
   
    
    delete [] y1;
    delete [] y2;
    delete [] y3;
    delete [] y1_1;
    delete [] y2_1;
    delete [] y3_1;
    
}



   





