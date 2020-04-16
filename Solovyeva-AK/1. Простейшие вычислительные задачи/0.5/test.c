#include "libs.h"

static double zero (double x) {
    return 0;
}

static double identical (double x) {
    return x;
}

static double power2 (double x) {
    return x*x;
}

static double add1 (double x) {
    return x+1;
}

static double mul2 (double x) {
    return x*2;
}


int main(void) {
	double x, user_res[8], res;
	printf("x=");
	if (!scanf("%lf", &x)){
		printf("ERROR::incorrect data entered\n");
		return -1;
	}
	printf("\nUser results\n");
	struct {
        const char *name;
        FUN f;
        FUN g;
    } tests[] = {
        {"1. f = zero, g = zero", zero, zero},
        {"2. f = zero, g = identical", zero, identical},
        {"3. f = identical, g = identical", identical, identical},
        {"4. f = identical, g = add1", identical, add1},
        {"5. f = identical, g = power2", identical, power2},
        {"6. f = add1, g = zero", add1, zero},
        {"7. f = add1, g = add1", add1, add1},
        {"8. f = power2, g = add1", power2, add1},
    };
    
    for(int i = 0; i < 8; i++) {
        if(!scanf("%lf", &user_res[i])) {
			printf("ERROR::incorrect data entered\n");
			return -1;
		}
    }
    
    for(int test_num = 0; test_num < 8; test_num++)
    {
		
        res = search(tests[test_num].f, tests[test_num].g, x);
        printf("min y with test functions '%s', res = %.6lf and it's ", tests[test_num].name, res);
        if (compare(user_res[test_num], res)) {
			printf("OK \n"); 
		} else {
			printf("NOT OK \n");
		}
    }
    return 0;
}
