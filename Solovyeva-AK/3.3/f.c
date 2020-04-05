#include "libs.h"

double shredding_sizing_grid (double f(double), double a, double b, double eps, ErrorCode *perr){
    if(perr != NULL)
        *perr = INT_OK; 
    coefficients parab;
    int n = 10;
    double h = (b - a)/n , min = f(a), min_x = a, tmp;
    double x1 = a, x2 = b, x3, x4, x5;
    while (h > 0.1) {
        h = (x2 - x1)/n;
        for (int i = 0; i <= n; i++) {
            tmp = f(x1+i*h);
            if (tmp < min) {
                min_x = x1+i*h;
                min = tmp;
            }
        }
        x1 = min_x - h;
        if (x1 < a) {
            x1 = a;
        }
        x2 = min_x + h;
        if (x2 > b) {
            x2 = b;
        }
    }
    x1 = min_x - h;
    x2 = min_x;
    x3 = min_x + h;
    parab = parabola(f, x1, x2, x3);
    do {
        if (parab.c2 != 0) {
            x4 = - parab.c1 / (2 * parab.c2);
        } else if (f(a) < f(b)) {
            return f(a);
        } else {
            return f(b);
        }
        if (x4 < a) {
            return f(a);
        } else if (x4 > b) {
            return f(b);
        }
        if (x4 > x2) {
            x1 = x2;
            x2 = x4;
        } else {
            x3 = x2;
            x2 = x4;
        }
        parab = parabola(f, x1, x2, x3);
        x5 = - parab.c1 / (2 * parab.c2);
    } while (!compare(f(x4), f(x5), eps));
    return f(x4);
}



//w
coefficients parabola (double f(double), double x1, double x2, double x3) {
    double **matrix = malloc(sizeof(double *) * 3);    
    for (int i = 0; i < 3; i++) {        
        matrix[i] = malloc(sizeof(double) * 4);    
    }
    matrix[0][0] = x1*x1;
    matrix[0][1] = x1;
    matrix[0][2] = 1;
    matrix[0][3] = f(x1);
    matrix[1][0] = x2*x2;
    matrix[1][1] = x2;
    matrix[1][2] = 1;
    matrix[1][3] = f(x2);
    matrix[2][0] = x3*x3;
    matrix[2][1] = x3;
    matrix[2][2] = 1;
    matrix[2][3] = f(x3);
    
    
    coefficients x = gauss(3, matrix);
    for (int i = 0; i < 3; ++i) {        
        free(matrix[i]);    
    }    
    free(matrix);
    return x;
}

//w
coefficients gauss(int n, double **matrix_now) {    
    double *x = malloc(sizeof(double) * n);
    coefficients c;
    double **matrix = malloc(sizeof(double *) * n);    
    for (int i = 0; i < n; i++) {        
        matrix[i] = malloc(sizeof(double) * (n + 1));    
    }    
    for (int i = 0; i < n; i++) {        
        for (int j = 0; j < n + 1; j++) {            
            matrix[i][j] = matrix_now[i][j];        
        }    
    }    
    const double eps = 0.000001;    
    for (int k = 0; k < n; k++) {        
        for (int i = k; i < n; i++) {              
        double tmp = matrix[i][k];            
        if (fabs(tmp) < eps) continue;            
        for (int j = 0; j < n + 1; j++)            
        matrix[i][j] = matrix[i][j] / tmp;            
        if (i == k) continue;            
        for (int j = 0; j < n + 1; j++)                
        matrix[i][j] = matrix[i][j] - matrix[k][j];        
        }    
    }   
    for (int k = n - 1; k >= 0; k--) {        
        x[k] = matrix[k][n];
            for (int i = 0; i < k; i++)
                matrix[i][n] = matrix[i][n] - matrix[i][k] * x[k];
    }    
    for (int i = 0; i < n; ++i) {        
        free(matrix[i]);    
    }    
    free(matrix);
    c.c2 = x[0];
    c.c1 = x[1];
    c.c0 = x[2];
    return c;
}

//w		
double max_2_dbl (double x, double y){
	if (x < y) {
		return y;
	} else {
		return x;
	}
}
//w
double max_3_dbl (double x, double y, double z) {
	return max_2_dbl(max_2_dbl(x,y), z); 
}
//w
int compare(double x, double y, double eps) {
	if (fabs(x-y) < (eps* max_3_dbl(x, y, 1))) {
		return 1;
	} else {
		return 0;
	}
}

