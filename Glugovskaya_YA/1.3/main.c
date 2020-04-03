#include<stdio.h> 
#include<stdlib.h>
#include"solve.h"
#include<math.h>
#include"test.h"

int main(void)
{
	double a,b,e,x, corAn;
	int res;
	
	
	printf("input eps\n");
	
	if(scanf("%lf",&e)!=1)
	{
		printf("cannot read eps\n");
		return 2;
	}
	
	a = 0;
	b = 5;
	res = solve(a,b,e,&x,func1);
	printf("\nИтерации=%d Корень=%lf\n",res,x);
	corAn = 2.142397398973329;
	printf("%lf\n", corAn-x);
	if (fabs(corAn-x)<e) printf("Correct answer\n");
	
	res = solve(a,b,e,&x,func);	
	printf("\nИтерации=%d Корень=%lf\n",res,x);
	corAn = 1.70977; 
	printf("%lf\n", corAn-x);
	if (fabs(corAn-x)<e) printf("Correct answer\n");
	

	
	a = -1;
	b = 0;
	res = solve(a,b,e,&x,func2);
	printf("\nИтерации=%d Корень=%lf\n",res,x);
	corAn = -0.337571;
	printf("%lf\n", corAn-x);
	if (fabs(corAn-x)<e) printf("Correct answer\n");
	return 0;
}