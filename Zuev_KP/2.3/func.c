#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"func.h"

int skal(int *a, int *b, int n, RRFUN fsum, RRFUN fproz)


{
     	int res = 0;
	if (n == 0)
	{
	return 0;
	}
	res = (*fproz)(a[0], b[0]);
	for(int i = 1; i < n; i++)
	{
		res = (*fsum)(res, (*fproz)(a[i], b[i]));
	}
	return res;
}





