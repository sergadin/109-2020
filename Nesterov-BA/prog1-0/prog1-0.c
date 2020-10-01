#include <stdlib.h>
#include "prog1-0.h"


double *result(fpointer f,  double *x, int n){
    double *foutput = (double*) malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++){
        foutput[i] = (*f)(x[i]);
    }
    return foutput;
}
