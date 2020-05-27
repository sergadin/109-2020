#include <stdio.h>
#include <malloc.h>
#include "Zhukova_z1.h"

int main (void)
{

        int i, j, k, m, n;
        FILE * input, * output;
        char ** mass;
        int     len;

        input = fopen ("input.txt", "r");
        output = fopen ("result.txt", "w");

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


	fscanf (input, "%d", &m);
	fscanf (input, "%d", &n);
//printf ("m1\n");

        if (( n < 1) || (m<1))
        {
                fclose (input);
                fclose (output);
                return -1;
        }

        mass = (char **)malloc(n*m * sizeof (char *));
        if (mass == NULL)
        {
                fclose (input);
                fclose (output);
                return -1;
        }
//printf ("%d %d m2\n", m, n);
	fseek(input, 1, SEEK_CUR);

        for (i=0;i<m*n;i++)
        {
//       		 for (j=0;j<n;j++)
//       		 {
                        len=255;
			mass[i]= (char *)malloc(255 * sizeof (char));
			getline ((char **)&mass[i],(size_t *)&len, input);
//		 }
//printf("i=%d\n", i);
	}
//printf ("m3\n");
	funcMass (m, n, mass);

	for (i=0; i<m; i++)
	{
		for (j=0; j<n; j++)
		{
			fprintf (output, "%s", mass[i*m+j]);
		}
	//	fprintf (output, "\n");
	}

	free(mass);
	fclose (input);
	fclose (output);
	return 0;
}
