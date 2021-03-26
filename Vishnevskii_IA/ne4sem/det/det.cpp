#include<stdio.h>
#include<stdlib.h>
#include<math.h>

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
   
  fprintf(out, "%lf ", det(a, n)); 
  
  fclose(in);
  fclose(out);
  free(a);
  return 0;  
}
