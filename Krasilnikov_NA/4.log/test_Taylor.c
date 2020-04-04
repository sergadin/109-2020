#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Taylor.h"

int main()
{
	FILE *fin, *fout;
	int i, m;
	double a, b, epsilon, *answers, *X;
	double answer;
	double espilon = 0.000001;
	ErrorCode le; //log_error
	RRFUN funcs[] = {first, second, third, fourth, fifth, sixth, seventh, eighth};
	m = 8;
	if ((fout = fopen("output.txt","w")) == NULL)
	{
		printf("INVALID OUTPUT FILE");
		return -1;
	}
	if ((answers = (double*) malloc(m * sizeof(double))) == NULL)
	{
		printf("MEMORY ALLOCATION ERROR");
		fclose(fout);
		return -1;
	}
	double answers[] = {log(1.23), log(0.34), log(1.99), log(1.47), log(0.47) , log(1), log(1.68), log(0.71)};
	double X[] = {1.23, 0.34, 1.99, 1.47, 0.47, 1, 1.68, 0,71};
	for(i = 0; i < m; i++)
	{
		answer = series(X[i], epsilon, funcs[i], &le);
		if (le == LOG_NEOK)
		{
			fprintf(fout, "Test № %d: LOSS\n", (i + 1));
			fprintf(fout, "Impossible to calculate\n");
			fclose(fout);
			free(answers);
			return -1;
		}
		if (fabs(answer - answers[i]) <= epsilon)
		{
			fprintf(fout, "Test № %d: OK | ", (i + 1));
			fprintf(fout, "Calculated value: %lf | ", answer);
			fprintf(fout, "Exact value: %lf | ", answers[i]);
			fprintf(fout, "Error value: %lf\n", fabs(answer - answers[i]));
		}
		else
		{
			fprintf(fout, "Test № %d: LOSS\n", (i + 1));
			fclose(fout);
			free(answers);
			return -1;
		}
	}
	fclose(fout);
	free(answers);
	return 0;
}
