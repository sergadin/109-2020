#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"func.h"


double findroot(double a, double b, double eps, RRF func)
{
	double end1 = a, mid = (a + b)/2, end2 = b ;
	double fend1, fmid, fend2;
	double lennow = b - a;
	if((*func)(end1)*(*func)(end2) >= 0)
		return b+100000;
	while(lennow > eps)
	{
		mid = (end1 + end2)/2;
		fend1 = (*func)(end1);
		fend2 = (*func)(end2);
		fmid = (*func)(mid);
		if(fmid*fend1 <= 0)
		{
			end2 = mid;
		}
		else
		{
			end1 = mid;
		}
		lennow = end2 - end1;
	}
	return (end1 + end2)/2;
}
