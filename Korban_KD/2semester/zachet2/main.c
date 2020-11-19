#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matr.h"
#include "solve55.h"
enum RETURN_CODES
{
    INPUT_ERROR = -3,
    MEMORY_ERROR,
    READ_ERROR,
};

int main(int argc, char **argv)
{
    double *a;
    int n, m;
    char *name = 0;
    clock_t time_start;
    int res_read;

    if( !(argc==4) || (n = atoi(argv[1]))<=0 || (m = atoi(argv[2]))<=0)
    {
        fprintf(stderr, "Usage: %s [n] [m] [file] (matrix n x m)\n", argv[0]);
        return INPUT_ERROR;
    }

    name = argv[3];

    if( !(a = (double*)malloc(n*m*sizeof(double))) )
    {
        fprintf(stderr, "Memory ERROR!\n");
        return MEMORY_ERROR;
    }
    
    
    res_read = read_matrix(a, n, m, name );
    
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
    
    solve55(a, n, m);
    
    printf("Elapsed %.2lf\n", (double)(clock() - time_start)/CLOCKS_PER_SEC);
    
    printf("solution\n");
    
    print_matrix(a, n, m);
    
    free(a);
    return 0;
} 
