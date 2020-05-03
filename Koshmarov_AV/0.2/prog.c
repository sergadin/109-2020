#include "help.h"


double *result(pointer_on_func our_func, double *ans,  double *point_x, double *point_y, int n){
    for (int i = 0; i < n; i++){
        ans[i] = (*our_func)(point_x[i], point_y[i]);
    }
    return ans;
}
