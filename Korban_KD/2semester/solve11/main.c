#include <stdio.h>
#include <math.h>
#include "find_root.h"
#include "../lib/exmath.h"
#include "integration.h"
#include "solve11.h"




int main(int argc, char** argv)
{
    double root, value, alpha, eps_i = 1e-8, eps_r = 1e-8;
    int iter;
    if( (argc != 4) || (sscanf(argv[1], "%lf", &alpha) != 1 ) || (sscanf(argv[2], "%lf", &eps_i) != 1 ) || (sscanf(argv[3], "%lf", &eps_r) != 1 ) )
    {
        fprintf(stderr, "Usage: %s [alpha] [accuracy for integration] [accuracy for finding root]\n", argv[0]);
        return -1;
    }
    
    iter = solve11(alpha, &root, eps_i, eps_r);
    value  = func_11_from_x(root) ;
    printf("root=%lf value=%lf difference: %e\niterartions for finding root:%d, total calls of function:%d\n", root, value, fabs(alpha - value), iter, getcount());
    
    return 0;
}

