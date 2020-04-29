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
    double eps, true_res[6], res;
	ErrorCode err;
	
	
	printf("Numerical precision (> 10^(-9)) - eps = ");
	if (!scanf("%lf", &eps)){
		printf("ERROR::incorrect data entered\n");
		return -1;
	}
	
	struct {
        const char *name;
        FUN f;
        double a;
        double b;
    } tests[] = {
        {"1. f = x", identical_x, -100, 100},
        {"2. f = x^2 + 2", x_power_2_plus_2, -100, 100},
        {"3. f = x^2-4", x_power_2_minus_4, -100, 100},
        {"4. f = x^3 + x^2 + 2", x_power_3, -0.5, 3},
        {"5. f = x + 2^x", logarifm, -100, 100},
        {"6. f = e^x", e_power_x, 0, 3},
    };
        	
    true_res[0] = -100;
    true_res[1] = 2;
    true_res[2] = -4;
    true_res[3] = 2;
    true_res[4] = -100;
    true_res[5] = 1;
    


    
    
    for(int test_num = 0; test_num < 6; test_num++) {
		printf("\nStart of the segment - a = %.0lf \n", tests[test_num].a);
        printf("End of the segment - b = %.0lf \n\n", tests[test_num].b);
        res = shredding_sizing_grid(tests[test_num].f, tests[test_num].a, tests[test_num].b, eps, &err);
		switch(err) {
			case INT_LIMITS:
                printf("Division by zero. Eror code: %d\n", err);
                return -1;
			case INT_CONVERGENCE:
                printf("No convergence. Eror code: %d\n", err);
                return -1;
			case INT_OK:
		
                printf("With test functions %s res = %.8lf \n    True answer is %.8lf \n    And it's ", 
                        tests[test_num].name, res, true_res[test_num]);
                if (compare(true_res[test_num], res, eps)) {
                    printf("correct! \n"); 
                } else {
                    printf("incorrect :c \n");
                }
            break;
        }
    }
    return 0;
}
