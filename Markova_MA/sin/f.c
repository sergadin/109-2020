#include "f.h"
#include <math.h>
double ab (double m) 
{
	if(m < 0)
	{
		return -m;
	}
	else
	{
		return m;
	}
}

double sin_(double x, double eps){
    int count = 0, n = 2;
    double now = x, ans = 0;
    while(now >= eps && count < 100){
        ans += now;
		now = -now*x*x/(n*(n + 1));
		n += 2;
		count++;
    }
    return answer;
}
