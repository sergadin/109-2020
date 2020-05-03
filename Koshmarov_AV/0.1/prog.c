#include <stdlib.h>
#include "help.h"


double *result(pointer_on_func our_func,  double *point, int n){
    double *ans = (double*) malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++){
        ans[i] = (*our_func)(point[i]);
    }
    return ans;
}
