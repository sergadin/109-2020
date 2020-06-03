#include <math.h>
#include <stdio.h>
#include "solve55.h"

static int find_place(double *a, int n, int m);
static double dot_protuct(double *a, int n, int m, int i, int j , int k);
static void replace(double *a, int n, int m, int k);

 static int find_place(double *a, int n, int m)
{
    int min_j = m; //row
    int min_i = 0; //colum
    for(int i = 0; i < n; i++)
    {
        double sum = 0;
        double min;
        int temp_min_j = 0;
        int flag = 0;
        
        for(int j = 0; j < m; j++) // finding of sum/m
        {
            sum += a[i*m + j];
        }
        
        sum = sum/m;
        
        for(int j = 0; j < m; j++) // finding minimum 
        {
            
            if( !(flag) && (a[i*m + j] > sum) ) // first minimum
            {
                min = a[i*m + j];
                flag = 1;
                temp_min_j = j;
            }
            
            if( (flag) && (a[i*m + j] > sum) && (a[i*m + j] < min) )
            {
                min = a[i*m + j];
                temp_min_j = j;
            }
        }
        
        if(min_j > temp_min_j)
        {
            min_j = temp_min_j;
            min_i = i;
        }
        
        //printf("row:%d arithmetic mean=%lf min=%lf min_i:%d min_j:%d\n", i, sum, min, min_i, min_j);
    }
    return min_i;
}


static double dot_protuct(double *a, int n, int m, int i, int j , int k)
{
    (void)n;
    (void)m;
    return (a[i*m] * a[k*m]) + (a[i*m + 1] * a[k*m + 1]) + (a[i*m + j] * a[k*m + j]);
}


 static void replace(double *a, int n, int m, int k)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 2; j < m; j++)
        {
            a[i*m + j] = dot_protuct(a, n, m ,i ,j, k);
        }
    }
}



void solve55(double *a, int n, int m)
{
    int row = find_place(a, n, m);
    replace(a, n, m, row);
}




