#include "prototype_4.h"
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

long long int Factorial(int n){
    if (n > 1) {
        return n*Factorial(n-1);
    } else {
        return 1;
    }
}

double funcRemainder(double x, int count){
    return pow(ab(x),count + 2) / funcFactorial(count + 2);
}

double sin_(double x, double eps){
    int count = 1;
    double answer = 0;
    while(funcRemainder(x, count) >= eps && count < 100){
        answer += pow(-1, (count - 1) / 2) * pow(x,count) / Factorial(count);
        count += 2;
    }
    return answer;
}
