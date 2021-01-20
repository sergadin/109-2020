#include <stdio.h>
#include <malloc.h>
#include "zachet2.h"
int main (void)
{

        int i, j, m, n;
        FILE * input, * output;
        double * a;
	double k;

        input = fopen ("input.txt", "r");
        output = fopen ("output.txt", "w");

        if (input == NULL)
        {
                fclose (input);
                fclose (output);
	        return -1;
        }
        else
        {
                if (output == NULL)
                {
        	        fclose (input);
	                fclose (output);
                        return -1;
                }
        }

	fscanf (input, "%d", &n);
	fscanf (input, "%d", &m);

        if ( (n < 1) || (m < 1) )
        {
                fclose (input);
                fclose (output);
                return -1;
        }

	i=0;
	while (fscanf(input, "%lf", &k)==1)
	{
		i = i+1;
	}
	if (i != m*n)
	{
printf("p1\n");
                fclose (input);
                fclose (output);
                return -1;
	}
	fseek (input, 0, 0);
	fscanf (input, "%d", &n);
	fscanf (input, "%d", &m);


        a = (double *)malloc((n*m) * sizeof (double));

        if (a == NULL)
        {
                fclose (input);
                fclose (output);
                return -1;
        }

//        fseek (input, 0, 0);

        for (i=0;i<(n);i++)
        {
		for (j=0;j<m;j++)
		{
                	fscanf (input, "%lf", &k);
                	a[i*m+j] = k;
		}
        }


	func (n, m, a);

	for (i=0; i<n; i++)
	{
		for (j=0;j<m;j++)
		{
			fprintf(output, "%f ", a[i*m+j]);
		}
		fprintf(output, "\n");
	}

	free (a);
	fclose (input);
	fclose (output);
}
