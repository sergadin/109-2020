#include <stdio.h>
#include <math.h>
#include "find_root.h"
#include "../lib/exmath.h"
#include "integration.h"
#include "solve11.h"


static double func_11_x_t(double t, double x);
static double func_11_from_x_root(double x);

static double alpha;
static int count = 0; // number of calls of func_11_from_x_root 
static double eps_i = 1e-8; //accuracy for integration
static double eps_r = 1e-8; //accuracy for root   


int getcount(void)
{
    return count;
}

static double func_11_x_t(double t, double x)
{
    return (x - t)/sqrt(1 + t*t*t*t );
}

static double func_11_from_x_root(double x) // function for find_root
{
    double value;
    int iter;
    
    iter = integrate(&func_11_x_t, 0, x, eps_i, &value);
    
    //uncommet bellow if want to see interations for every call of function
    
    //printf(" x = %lf, value=%lf iterations for integration: %d\n", x, value, iter);
    
    (void)iter;
    count++;
    return value - alpha; 
}

double func_11_from_x(double x) // function to find f(x)
{
    double value;
    int iter;
    
    iter = integrate(&func_11_x_t, 0, x, eps_i, &value);
    
    //uncommet bellow if want to see interations for every call of function
    
    //printf(" x = %lf, value=%lf iterations for integration: %d\n", x, value, iter);
    
    (void)iter;
    count++;
    return value; 
}


/* function finds root of function 11
 * 
 * function 11 increases in value with increase in x
 * 
 * calculationg value of function 11 is significantly harder for values > 10000, so we want to decrease number of calls of this function
 * solve11 does it by getting closer to root from the right side
 * 
 * lim(x to inf)[f(x)/x] == 1.85.. therefore functioon 11 is almost linear on big values
 * 
 * solve11 sets right side as value/1.8, that way right side is very close to root
 */
int solve11(double value, double *root , double eps_integration, double eps_root)
{
    int iter;
    double right;
    alpha = value;
    eps_i = eps_integration;
    eps_r = eps_root;
    
    // if value > 500 than root is allways smaller than alpha/1.8 (found myself while testing)
    right = alpha/1.8;
    
    iter = find_root(&func_11_from_x_root, 0, right, eps_r, root);
    
    while( iter == NO_ROOT ) // if there are no roots from 0 to right: increase right and search again
    {
        right *= 1.8;
        iter = find_root(&func_11_from_x_root, 0, right, eps_r, root);
    }
    
    if(iter == UNABLE)
    {
        printf("cannot reach further accuracy\n");
        return 0;
    }
    
    if(iter == NOT_FOUND)
    {
        printf("iteration count for finding root is reached\n");
        return MAX_IT;
    }
    
    return iter;
}

