#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Taylor.h"

int main()
{
	FILE *fout;
	int i, m;
	double a, b;
	double answer;
	double epsilon = 0.000000001;
	ErrorCode le; //log_error
	m = 8;
	if ((fout = fopen("output.txt","w")) == NULL)
	{
		printf("INVALID OUTPUT FILE");
		return -1;
	}
	double answers[] = {log(1.23), log(0.34), log(1.99), log(1.47), log(0.47), log(1), log(1.68), log(0.71)};
	double X[] = {1.23, 0.34, 1.99, 1.47, 0.47, 1, 1.68, 0.71};
	for(i = 0; i < m; i++)
	{
		answer = series(X[i], epsilon, &le);
		if (le == LOG_NEOK)
		{
			fprintf(fout, "Test № %d: LOSS\n", (i + 1));
			fprintf(fout, "Impossible to calculate\n");
			fclose(fout);
			return -1;
		}
		if (fabs(answer - answers[i]) <= epsilon)
		{
			fprintf(fout, "Test № %d: OK | ", (i + 1));
			fprintf(fout, "Calculated value:");
			if (answer >= 0)
			{
				fprintf(fout, " ");
			}			
			fprintf(fout, " %1.11f | ", answer);
			fprintf(fout, "Exact value:");
			if (answers[i] >= 0)
			{
				fprintf(fout, " ");
			}
			fprintf(fout, " %1.11f | ", answers[i]);
			fprintf(fout, "Error value: %1.11f\n", fabs(answer - answers[i]));
		}
		else
		{
			fprintf(fout, "Test № %d: LOSS\n", (i + 1));
			fprintf(fout, "Calculated value:");
			if (answer >= 0)
			{
				fprintf(fout, " ");
			}
			fprintf(fout, " %1.11f | ", answer);
			fprintf(fout, "Exact value:");
			if (answers[i] >= 0)
			{
				fprintf(fout, " %1.11f | ", answers[i]);
			}
			fprintf(fout, "Error value: %1.11f\n", fabs(answer - answers[i]));
		}
	}
	fclose(fout);
	return 0;
}
