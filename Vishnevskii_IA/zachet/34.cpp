#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double sum(double *a, int i, int m); // сумма эл-ов строки i, которые по модулю больше первого эл-та строки i
int check(double *a, int n, int m); // строка, у которой sum максимальна
void sr(double *a, int n, int m); // вместо эл-та строки поставить среднее эл-та строки и эл-та check

double sum(double *a, int i, int m)
{
	int j;
	double s;
	
	s = 0;
	
	for(j = 0; j < m; j++)
	{
		if(fabs(a[i*m + j]) > a[i*m + 0])
		{
			s = s + a[i*m + j];
		}
	}
	
	return s;
}

int check(double *a, int n, int m)
{
	int i, imax;
	
	imax = 0;
	
	for(i = 0; i < n; i++)
	{
		if(sum(a, i, m) > sum(a, imax, m))
		{
			imax = i;
		}
	}
	
	return imax;
}

void sr(double *a, int n, int m)
{
	int i, j;
	
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < m; j++)
		{
			a[i*m + j] = (a[i*m + j] + a[check(a, n, m)*m + j])/2;
		}
	}
}

int main(void)
{
	FILE *in, *out;
	double *a; 
	int i, j, n = 0, m = 0;
	
	in = fopen("input.txt","r");
   out = fopen("output.txt","w");
   
   if (in == NULL || out == NULL) 
   {
       return -1;
   }
   
   if (fscanf( in, "%d", &n) != 1) 
   {
      fclose(in);
      fclose(out);
      return -1;
   }
   
   if (fscanf( in, "%d", &m) != 1) 
   {
       fclose(in);
       fclose(out);
       return -1;
   }
   
   if (n < 1 || m < 1) 
   {
       fclose(in);
       fclose(out);
       return -1;
   }
   
   a = (double*)malloc(n*m*sizeof(double));
   
   if (!a)
   {
      free(a);
      fclose(in);
      fclose(out);
      return -1;
   }
   
    for (i = 0; i < n; i ++)
   {
       for (j = 0; j < m; j++)
       {
             if (fscanf( in, "%lf", &a[i*m + j ]) != 1) 
             {
                  free(a);
                  fclose(in);
                  fclose(out);
                  return -1;
             }
       }
   }
   
   sr(a, n, m);
   
   fprintf( out, "%d ", n);
   fprintf( out,"%d", m);
   fprintf( out, "\n");
   
   for ( i = 0 ; i < n ; i++)
  {
      for( j = 0 ; j < m ; j++)
      {
          fprintf(out , "%lf " , a[i*m + j ] ); 
      }
        fprintf(out , "\n");
  }
  
  fclose(in);
  fclose(out);
  free(a);
  return 0;  
}
