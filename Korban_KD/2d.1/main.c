#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "matr.h"
#include "rank.h"
#include "../lib/exmath.h"

enum RETURN_CODES
{
    INPUT_ERROR = -3,
    MEMORY_ERROR,
    READ_ERROR,
};

int main(int argc, char **argv)
{
    double **a;
    int n, m, k, res;
    char *name = 0;
    clock_t time_start;
    
    
    if( !(argc==3 || argc==4) || (n = atoi(argv[1]))<=0 || (m = atoi(argv[2]))<=0 )
    {
        fprintf(stderr, "Usage: %s (matrix n x m) [n] [m] [file] (test mode w/o file ) (n rows m colums)\n", argv[0]);
        return INPUT_ERROR;
    }

    if( argc==4 )
    {
        name = argv[3];
    }

    if( !(a = (double**)malloc(n*sizeof(double*))) )
    {
        fprintf(stderr, "Memory ERROR!\n");
        return MEMORY_ERROR;
    }
    
    for(int i = 0; i < n; i++)
    {
        if( !(a[i] = (double*)malloc(m*sizeof(double))) )
        {
            fprintf(stderr, "Memory ERROR!\n");
            return MEMORY_ERROR;
        }
    }

    if( name )
    {
        int res_read;

        res_read = read_matrix(a, n, m, name);

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

            for(int i = 0; i < n; i++)
            {
                free(a[i]);
            }
            free(a);
            return READ_ERROR;
        }
        printf("ROWS AND COLUMS ARE COUNTED FORM 0\n\n");
        printf("matrix\n");
        print_matrix(a, n, m);

        time_start = clock();
    
        res = rank_matrix(a, n ,m);
    
        printf("Elapsed %.2lf\n", (double)(clock() - time_start)/CLOCKS_PER_SEC);
        printf("redused row echelon form\n");
        print_matrix(a, n, m);
        
        printf("rank=%d\n", res);
        
    } 
    else
    {
        for(k = 1; k <= 6; k++)
        {
            init_matrix(a, n , m , k);
            printf("ROWS AND COLUMS ARE COUNTED FORM 0\nk==%d\n\n",k);
            printf("matrix\n");
            print_matrix(a, n, m);

            time_start = clock();
    
            res = rank_matrix(a, n ,m);
    
            printf("Elapsed %.2lf\n", (double)(clock() - time_start)/CLOCKS_PER_SEC);
            printf("redused row echelon form\n");
            print_matrix(a, n, m);
            printf("rank=%d\n", res);
        
            printf("/////////////////////////////////////////////////////////\n");

        }
    }
    for(int i = 0; i < n; i++)
    {
        free(a[i]);
    }
    free(a);
    return 0;
} 
