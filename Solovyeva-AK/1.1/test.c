#include "libs.h"

static double identical_x (double x) {
    return x;
}

static double x_power_2_plus_2 (double x) {
    return x*x + 2;
}
 
static double x_power_2_minus_4 (double x) {
    return x*x - 4;
}
       
static double x_power_3(double x) {
    return (x*x*x + x*x + 2);
}

static double logarifm(double x) {
    return x+pow(2,x);
}

static double e_power_x (double x) {
    return exp(x);
}

int main(void) {
	double a = -100, b = 100, eps, true_res[6] =  {0, -1, -2, -1.69562077, -0.64118574, -1};
	struct eq res;
	
	printf("Start of the segment - a = -100 \n");
	printf("End of the segment - b = 100 \n");
	
	printf("Numerical precision (> 10^(-9)) - eps = ");
	if (!scanf("%lf", &eps)){
		printf("ERROR::incorrect data entered\n");
		return -1;
	}
	
	struct {
        const char *name;
        FUN f;
    } tests[] = {
        {"1. f = x", identical_x},
        {"2. f = x^2 + 2", x_power_2_plus_2},
        {"3. f = x^2-4", x_power_2_minus_4},
        {"4. f = x^3 + x^2 + 2", x_power_3},
        {"5. f = x + 2^x", logarifm},
        {"6. f = e^x", e_power_x},
    };
 
    for(int test_num = 0; test_num < 6; test_num++) {
		res = root(tests[test_num].f, a, b, eps);
		if (res.value != -1) {
			printf("With test functions %s root = %.8lf \n    True answer is %.8lf \n    Number of iterations is %d\n    And it's ", 
			tests[test_num].name, res.value, true_res[test_num], res.quantity);
			if (compare(true_res[test_num], res.value, eps)) {
				printf("correct! \n"); 
			} else {
				printf("incorrect :c \n");
			}
		} else {
			printf("With test functions %s :\n    The sings at the ends of segment are the same\n", tests[test_num].name);
			
		}
    }
    return 0;
}
