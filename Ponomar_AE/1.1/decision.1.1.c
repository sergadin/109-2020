#include <stdio.h>
#include <math.h>
#include "decision.1.1.h"

double dcsn_f_x(double X_1, double X_2, double E, RRF func)
{
        double left = X_1, mid = (X_1+X_2)/2, right = X_2, f_left, f_mid, f_right, cur_length = X_2-X_1;

        if((*func)(left)*(*func)(right) >= 0)
                return 10000;

        while(cur_length > E)
        {
                mid = (left+right)/2;
                f_mid = (*func)(mid);
                if(f_mid*f_right <= 0)
                {
                        left = mid;
                        f_left = f_mid;
                }
                else
                {         
                        right = mid;
                        f_right = f_mid;
                }
                cur_length = right-left;
        }

        return (left+right)/2;
}

