#include "libs.h"

static double zero (double x) {
    return x*0;
}

static double identical_x (double x) {
    return x;
}

static double x_power_2 (double x) {
    return x*x;
}
    
static double sin_x (double x) {
    return sin(x);
}

static double e_power_x (double x) {
    return exp(x);
}

static double cos_x (double x) {
    return cos(x);
}

int main(void) {
	double a = -1, b = 3, n, eps, true_res[6], res;
	
	printf("Start of the segment - a = -1 \n");
	printf("End of the segment - b = 3 \n");
	
	printf("Numerical precision (> 10^(-9)) - eps = ");
	if (!scanf("%lf", &eps)){
		printf("ERROR::incorrect data entered\n");
		return -1;
	}
	
	struct {
        const char *name;
        FUN f;
    } tests[] = {
        {"1. f = 0", zero},
        {"2. f = x" ,identical_x},
        {"3. f = x^2", x_power_2},
        {"4. f = sin(x)", sin_x},
        {"5. f = cos(x)", cos_x},
        {"6. f = e^x", e_power_x},
    };
    
        	
    true_res[0] = 0;
    true_res[1] = 4;
    true_res[2] = 9.33333333;
    true_res[3] = 1.53002948;
    true_res[4] = 0.98259099;
    true_res[5] = 19.71765748;
    
    for(int test_num = 0; test_num < 6; test_num++) {
		res = integral(tests[test_num].f, a, b, eps);
        printf("With test functions %s integral = %.8lf \n    True answer is %.8lf \n    And it's ", 
        tests[test_num].name, res, true_res[test_num]);
        if (compare(true_res[test_num], res, eps)) {
			printf("correct! \n"); 
		} else {
			printf("incorrect :c \n");
		}
    }
    return 0;
}
