#include <stdio.h>
#include <math.h>
#include <time.h>
#include "sin.h"
#define READ_ERROR -1


int main (int argc, const char **argv)
{
    double x, eps, res;
    
    if(argc != 3 || sscanf(argv[1], "%lf", &x)!=1 || sscanf(argv[2], "%lf", &eps)!=1 )
    {
        fprintf(stderr, "Usage : %s [x] [eps] \n", argv[0]);
        return READ_ERROR;
    }
    
    res = _sin(x, eps);
    printf(" sin_(%lf)=%.16lf\tdifference=%.16lf\n", x, res, fabs(res - sin(x)));
    return 0;
}
