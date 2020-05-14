#include "libs.h"

int main(void) {
	double eps, res[6], true_res[6], x[6] = {0, -2, 0.33333333, 0.53002948, -0.58259099, 19.71765748};
    
    for (int i = 1; i < 6; i++)  {
		true_res[i] = log(1 + x[i]);
	}
	
	printf("ln(1+x), -1 < x < 1\n");
	printf("Numerical precision (> 10^(-9)) - eps = ");
	if (!scanf("%lf", &eps)){
		printf("ERROR::incorrect data entered\n");
		return -1;
	}
	
	printf("%.8lf", logarifm(x[4], eps));

	for(int test_num = 0; test_num < 6; test_num++) {
		if ((x[test_num] < 1.0) && (x[test_num] > -1.0)) {
			res[test_num] = logarifm(x[test_num], eps);
			printf("%d. x = %.8lf \n   ln(1+x) = %.8lf and it's ", test_num+1, x[test_num], res[test_num]);
			if (compare(true_res[test_num], res[test_num], eps)) {
				printf("correct! \n"); 
			} else {
				printf("incorrect :c \n   True answer is %.8lf \n", true_res[test_num]);
			}
		} else {
			printf("%d. Impossible wiht x = %.8lf \n",test_num+1, x[test_num]);
		}
	}
	return 0;
}




