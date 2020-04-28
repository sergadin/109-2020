#include <stdio.h>
#include <math.h>
#include "matr.h"
#define M_MAX 10
#define N_MAX 10

int read_matrix(double **a, int m, int n, const char *name)
{
    FILE *file;
    int i, len = m*n;

    if( !(file = fopen(name, "r")) )
        return MATR_ERR_OPEN;

    for( i = 0; i<len; i++ )
    {
        for(int j = 0; j < m; j++)
        {
            if( fscanf(file, "%lf", a[i[j]] )!=1 )
            fclose(file);
            return MATR_ERR_READ;
        }

    fclose(file);
    return MATR_SUCCESS;
}

double f1(int n, int i, int j)
{
     (void)n;
     return n - (i>j ? i : j) + 1 ;
}

double f3(int n, int i, int j)
{
    (void)n;
    return fabs((double)(i-j));
}

double f4(int n, int i, int j)
{
    (void)n;
    return 1/((double)i + (double)j + 1);
}

void init_matrix(double **a, int n, int k)
{
    int i, j;

    if (k==1)
    {
        for( i = 0; i < n; i++ )
            for( j = 0; j < n; j++ )
                a[i][j] = f1(n, i, j);
    }
    if(k==2)
    {
        for( i = 0; i < n; i++ )
            for( j = 0; j < n; j++ )
                a[i][j] = fmax(i, j);
    }
    if(k==3)
    {
        for( i = 0; i < n; i++ )
            for( j = 0; j < n; j++ )
                a[i][j] = f3(n, i, j);
    }
    
    if(k==4)
    {
        for( i = 0; i < n; i++ )
            for( j = 0; j < n; j++ )
                a[i][j] = f4(n, i, j);
    }
}

 void init_vector(double *b, double *a, int n)
 {
     for(int i = 0; i < n; i++)
     {
         double sum = 0;
         for(int j = 1; j < n  ; j += 2)
         {
             sum += a[i*n +j];
         }
         b[i] = sum;
     }
}

void print_matrix(double *a, int m, int n)
{
    int i, j, m_max, n_max;

    m_max = (m>M_MAX ? M_MAX : m);
    n_max = (n>N_MAX ? N_MAX : n);

    for( i = 0; i<m_max; i++ )
    {
        for( j = 0; j<n_max; j++ )
            printf("\t%lf", a[i][j]);
        printf("\n");
    }
}

void print_vector(double *a, int n, int m)
{
    int n_max;
    
    n_max = m;
    (void)n;
    for(int i = 0; i < n_max; i++)
    {
        printf("\t%lf", a[i]);
    }
    printf("\n");
}


void transpos(double *a,int m, int n)
{
    double c;
    for(int i = 0 ; i < m; i++)
    {
        for(int j = i ; j < n; j++)
        {
            if( (i != j) )
            {
                c = a[i * n + j];
                a[i * n + j] = a[j * n + i];
                a[j * n + i] = c;
            }
        }
    }
}

void colum_swap(double *a,int m, int n, int i, int j )
{
    double c;
    double *pi = a + i;
    double *pj = a + j; 
    if ( (i > n) || (j > n) )
    {
        return;
    }
    
    for(int k = 0; k < m; k++)
    {
        c = pi[k*n];
        pi[k*n] = pj[k*n];
        pj[k*n] = c;
    }
        
    
}

void row_swap(double *a,int m, int n, int i, int j )
{
    double c;
    double *pi = a + i*n;
    double *pj = a + j*n; 
    if ( (i > m) || (j > m) )
    {
        return;
    }
    
    for(int k = 0; k < n; k++)
    {
        c = pi[k];
        pi[k] = pj[k];
        pj[k] = c;
    }
        
    
}

void delete_part(double *a, int m, int n, int i, int j)
{
    if( (i > -1) && (i < m - 1) )
    {
        for (int k = i; k < (m - 1) ; k++)
        {
            for(int l = 0; l < n; l++)
            {
                a[k*n + l] = a[(k + 1)*n + l];
            }
        }
        
    }
    
    if(i == m - 1)
    {
        for(int l = 0; l < n; l++)
            {
                a[i*n + l] = 0;
            }
    }
    if( (j > -1) && (j < n))
    {
        int step = 0;
        for(int k  = 0; k < (n - 1) * (m - (i>-1 ? 1 : 0) ); k++)
        {
            if( (k + step)%n == j)
                step++;
//             printf("%d %d\n", k, step);
            a[k] = a[k + step];
        }
    }
}

void row_substr(double *a,int m, int n, int i, int j, double b )
{
    double *pi = a + i*n;
    double *pj = a + j*n; 
    if ( (i > m) || (j > m) )
    {
        return;
    }
    
    for(int k = 0; k < n; k++)
    {
        pj[k] -= b*pi[k];
    }
}

void mult_vector(double *a, double *b, double *c, int m, int n)
{
    double sum;
    for(int i = 0; i < m; i++)
    {
        sum = 0;
        for(int j = 0; j < n;j++)
        {
            sum += a[i*n + j] * b[j];
        }
        c[i] = sum;
    }
}

double norm_matrix(double *a, int n ,int m)
{
    double sum = 0, max;
    for(int i = 0; i < n; i++)
    {
        sum = 0;
        for(int j = 0; j < m; j++)
        {
            sum = sum + a[i][j];
        }
        if(i == 0)
        {
            max = sum;
        }
        if ( (i != 0) && (max < sum) )
        {
            max = sum;
        }
    }
    return max;
}


double find_determinant (int n, double *a )
{
    double res = 1, norm_a = norm_matrix(a, n);
    for(int i = 0; i < n; i++)
    {
        int max_i;
        if ( find_max_abs_redused_colum(n, a, i , &max_i) < 1e-20*norm_a )
        {
            return 0;
        }
        if(max_i != i)
        {
            row_swap(a, n, n, max_i, i);
            res *= -1;
        }
        for(int j = i+1 ; j < n; j++)
        {
            for(int k = i +1  ; k < n; k++)
            {
                a[j*n + k] -= a[i*n +k]*(a[j*n + i]/a[i*n + i]);
            }
        
        }
    }
    for(int i = 0; i < n; i++)
    {
        res *= a[i*n + i ];
    }
    return res;
}


double find_max_abs_redused_colum(int n, double *a, int start, int  *max_i)
{
    double max = fabs(a[start*n +start]);
    *max_i = start;
    for(int i = start + 1; i < n; i++)
    {
        double temp = fabs(a[i*n + start]);
        if(max < temp)
        {
            max = temp;
            *max_i  = i;
        }
    }
    return max;
}


void mult_matrix(double *a, double *b, double *c, int m, int n, int k)
{
    double sum;
    
    for(int g = 0; g<k; g++)
    {
        for(int i = 0; i < m; i++)
        {
            sum = 0;
            for(int j = 0; j < n;j++)
            {
                sum += a[i*n + j] * b[j*k + g];
            }
            c[i*k + g] = sum;
        }
    }
}

double find_max_abs_redused(int n, double *a, int start, int  *max_i, int *max_j)
{
    double max = fabs(a[start*n +start]);
    *max_i = start;
    *max_j = start;
    for(int i = start; i < n; i++)
    {
        for(int j = start; j < n; j++)
        {
            double temp = fabs(a[i*n + j]);
            if( (i==start) && (j==start))
                continue;
            
            if( (max < temp) )
            {
                max = temp;
                *max_i = i;
                *max_j = j;
            }
        }
    }
    return max;
}

