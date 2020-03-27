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
	double a, b, n, user_res[5], res;
	
	printf("Start of the segment - a = ");
	if (!scanf("%lf", &a)) {
		printf("ERROR::incorrect data entered\n");
		return -1;
	}
	
	printf("End of the segment - b = ");
	if (!scanf("%lf", &b)) {
		printf("ERROR::incorrect data entered\n");
		return -1;
	}
	
	if (a > b) {
		printf("ERROR::segment parameters incorrected\n");
		return -1;
	}
	
	printf("Number of divisions - n = ");
	if (!scanf("%lf", &n)){
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
    
    for (int test_num = 0; test_num < 6; test_num++) {
		printf("%s\n", tests[test_num].name);
	}
			
	printf("Your supposedly correct answer: \n");
        	
    for (int i = 0; i < 6; i++) {
        if(!scanf("%lf", &user_res[i])) {
			printf("ERROR::incorrect data entered\n");
			return -1;
		}
    }
    
    for(int test_num = 0; test_num < 6; test_num++) {
		res = integral(tests[test_num].f, a, b, n);
        printf("With test functions %s true answer is integral = %.6lf \n    Your answer is ", tests[test_num].name, res);
        if (compare(user_res[test_num], res)) {
			printf("correct! \n"); 
		} else {
			printf("incorrect :c \n");
		}
    }
    return 0;
}
