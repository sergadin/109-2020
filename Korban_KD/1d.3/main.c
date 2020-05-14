#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "matr.h"
#include "invert_matrix.h"
#include "../lib/exmath.h"

enum RETURN_CODES
{
    INPUT_ERROR = -3,
    MEMORY_ERROR,
    READ_ERROR,
};

int main(int argc, char **argv)
{
    double *a, *b, *c;
    int n, m, k, res;
    char *name = 0;
    clock_t time_start;
    
    
    if( !(argc==2 || argc==3) || (n = atoi(argv[1]))<=0 )
    {
        fprintf(stderr, "Usage: %s (matrix n x n) [n] [file] (test mode w/o file )\n", argv[0]);
        return INPUT_ERROR;
    }

    if( argc==3)
    {
        name = argv[2];
    }

    if( !(a = (double*)malloc(n*n*sizeof(double))) )
    {
        fprintf(stderr, "Memory ERROR!\n");
        return MEMORY_ERROR;
    }
    
    if( !(b = (double*)malloc(n*n*sizeof(double))) )
    {
        fprintf(stderr, "Memory ERROR!\n");
        return MEMORY_ERROR;
    }
    
    if( !(c = (double*)malloc(n*n*sizeof(double))) )
    {
        fprintf(stderr, "Memory ERROR!\n");
        return MEMORY_ERROR;
    }

    if ( n > 8)
        m = 8;
    else
        m = n;
    if( name )
    {
        int res_read;

        res_read = read_matrix(a, n, n, name);

        if( res_read!=MATR_SUCCESS )
        {
            switch( res_read )
            {
                case MATR_ERR_OPEN:
                    fprintf(stderr, "ERROR can't open %s\n", name);
                    break;
                case MATR_ERR_READ:
                    fprintf(stderr, "ERROR can't read element from %s\n", name);
                    break;
                default:
                    fprintf(stderr, "Unknown ERROR code: %d\n", res_read);
            }

            free(a);
            return READ_ERROR;
        }
        
        printf("ROWS AND COLUMS ARE COUNTED FORM 0\n\n");
        printf("matrix\n");
        print_matrix(a, n, m);

        time_start = clock();
    
        res = invert_matrix(n, a, b);
    
        printf("Elapsed %.2lf\n", (double)(clock() - time_start)/CLOCKS_PER_SEC);
        
        if(res !=OK)
        {
            printf("determinant is 0\n");
            free(a);
            free(b);
            free(c);
            return 0;
        }
        printf("inverted matrix\n");
        print_matrix(b, n, m);
        
        printf("after multiplication\n");
        read_matrix(a, n, n, name);
        mult_matrix(a, b, c, n, n, n);
        print_matrix(c, n, m);
        
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {                
                if(i==j)
                    c[i*n + j] -= 1;
            }
        }
        
        printf("norm of error: %e\n", norm_matrix(c, n)/norm_matrix(a, n));
        
        
    } 
    else
    {
        for(k = 1; k <= 4; k++)
        {
            printf("ROWS AND COLUMS ARE COUNTED FORM 0\nk==%d\n", k);
            init_matrix(a, n, k);
            printf("matrix\n");
            print_matrix(a, n, m);

            time_start = clock();
    
            res = invert_matrix(n, a, b);
    
            printf("Elapsed %.2lf\n", (double)(clock() - time_start)/CLOCKS_PER_SEC);
            
            if(res !=OK)
            {
                printf("determinant is 0\n");
                free(a);
                free(b);
                free(c);
                return 0;
            }
            printf("inverted matrix\n");
            print_matrix(b, n, m);
            
            printf("after multiplication\n");
            init_matrix(a, n, k);
            mult_matrix(a, b, c, n, n, n);
            print_matrix(c, n, m);
            
            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < n; j++)
                {                
                    if(i==j)
                        c[i*n + j] -= 1;
                }
            }
        
            printf("norm of error: %e\n", norm_matrix(c, n)/norm_matrix(a, n));
        
            printf("/////////////////////////////////////////////////////////\n");

        }
        
    }
    
    free(a);
    free(b);
    free(c);
    
    return 0;
} 
