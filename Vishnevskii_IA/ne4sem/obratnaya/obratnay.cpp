#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void obr(double *a, int n);
double det(double *a, int n);

double det(double *a, int n)
{
	
	int i, j, k;
	double d;
	double *b;
	
	b = (double*)malloc((n-1)*(n-1)*sizeof(double));
	
	d = 0;
	
	if(n == 1)
	{
		return a[2];
	}
	
	if(n == 2)
	{
		
		d = a[1*n + 1] * a[2*n + 2] - a[2*n + 1] * a[1*n + 2];
		
		return d;
		
	}
	else
	{
		
		for(k = 1; k <= n; k++)
		{
			
			for(i = 2; i <= n; i++)
			{
				for(j = 1; j < k; j++)
				{
					b[(i - 1)*(n - 1) + j] = a[i*n + j];
				}
				
				for(j = k + 1; j <= n; j++)
				{
					b[(i - 1)*(n - 1) + (j - 1)] = a[i*n + j]; 
				}
			}
			
			d = d + a[1*n + k] * pow(-1, 1 + k) * det(b, n - 1);
			
		}

	}
	
	return d;
	
}

void obr(double *a, int n)
{
	int i, j, k, e;
	double *c, d;
	double *b;
	
	d = det(a, n);
	
	
	b = (double*)malloc((n-1)*(n-1)*sizeof(double));
	c = (double*)malloc((n-1)*(n-1)*sizeof(double));
	
	 for (i = 1; i <= n; i ++)
   {
       for (j = 1; j <= n; j++)
       {
       	
             b[i*n + j ] = a[i*n + j];
             
       }
   }
	
	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= n; j++)
		{
			
			for(k = 1; k < j; k++)
			{
				for(e = 1; e < i; e++)
				{
					c[k*(n-1) + e] = b[k*n + e];
				}
				for(e = i + 1; e <= n; e++)
				{
					c[k*(n-1) + (e-1)] = b[k*n + e];
				}
			}
			
			for(k = j+1; k <= n; k++)
			{
				for(e = 1; e < i; e++)
				{
					c[(k-1)*(n-1) + e] = b[k*n + e];
				}
				for(e = i + 1; e <= n; e++)
				{
					c[(k-1)*(n-1) + (e-1)] = b[k*n + e];
				}
			}

			
			a[i*n + j] = (pow(-1, i+j) * det(c, n-1)) / d; 
			
			
			
		
		}
		
		
	}
	
}



int main(void)
{
	FILE *in, *out;
	double *a; 
	int i, j, n = 0;
	
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
   
   if (n < 1) 
   {
       fclose(in);
       fclose(out);
       return -1;
   }
   
   a = (double*)malloc(n*n*sizeof(double));
   
   if (!a)
   {
      free(a);
      fclose(in);
      fclose(out);
      return -1;
   }
   
    for (i = 1; i <= n; i ++)
   {
       for (j = 1; j <= n; j++)
       {
             if (fscanf( in, "%lf", &a[i*n + j ]) != 1) 
             {
                  free(a);
                  fclose(in);
                  fclose(out);
                  return -1;
             }
       }
   }
   
   if(det(a, n) == 0)
   {
   	fprintf(out , "obratnoi net");
   	
   	return 0;
   }
   
   obr(a, n);
   
   fprintf( out, "%d ", n);
   fprintf( out, "\n");
   
   if(det(a, n) != 0)
   {
   	for ( i = 1 ; i <= n ; i++)
  {
      for( j = 1 ; j <= n ; j++)
      {
          fprintf(out , "%lf " , a[i*n + j ] ); 
      }
        fprintf(out , "\n");
  }
}
  
  fclose(in);
  fclose(out);
  free(a);
  return 0;  
}
