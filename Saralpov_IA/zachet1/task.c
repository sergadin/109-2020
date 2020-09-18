#include "task.h"
#include <math.h>
#include <stdio.h>

int find_row (double *data, int n_rows, int n_cols)
{
int  i, j, t=1;
double max, first_el1, s=0, s1=0;
    
    for (i=1; i<n_rows; i++)
    {
        first_el1 = EL(data, n_cols, 0, 0);
        if(fabs(EL(data, n_cols, 0, i))>fabs(first_el1))
        s1 += EL(data, n_cols, 0, i);
    }
    max = s1;
    for (i=0; i<n_rows; i++)
    {
        s=0;
        for(j=0; j<n_cols; j++)
        {
            if(fabs(EL(data, n_cols, i, j))>fabs(EL(data, n_cols, i, 0)))
            s += EL(data, n_cols, i, j);
        }
           
        if(s>max)
        {
            max=s;
            t=i+1;
        }
    }
return t; 
} 

void swapcols(double *data, int n_rows, int n_cols, int col1, int col2)
{
int i, j;
double t;
	for(i = 0; i < n_rows; i++)
	{

		t = EL(data, n_cols, i, col1);
		EL(data, n_cols, i, col1) = EL(data, n_cols, i, col2);
		EL(data, n_cols, i, col2) = t;
	}
}

void sort(double *data, int n_rows, int n_cols,int t)
{
int i, j;
    double tmp;

    for(j=0; j<n_cols-1; j++)
    {
        for(i=j+1; i<n_cols; i++)
        {
        if(EL(data, n_cols, t, i) > EL(data, n_cols, t, i-1))
                {
                swapcols(data, n_rows, n_cols, i, i-1); 
                }
        }
    }
}
void printmat(double *data, int n_rows, int n_cols,int t)
{
    int i,j;
	for(i = 0; i < n_rows; i++)
	{
		for(j = 0; j < n_cols; j++)
		{
			fprintf(stdout,"%g ",EL(data, n_cols, i, j));
		}
		fprintf(stdout, "\n");
	}

}
  
            
    
            
                    
        


