#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simpson.h"
double first(double x);
int main()
{
	FILE *fin, *fout, *ans;
	int i, m;
	double a, b, epsilon, result, *answers;
	RRFUN funcs[] = {first};
	m = 1;
	if ((fin = fopen("input.txt","r")) == NULL)
	{
		printf("INVALID INPUT FILE");
		return -1;
	}
	if ((ans = fopen("answers.txt","r")) == NULL)
	{
		printf("INVALID ANSWERS FILE");
		fclose(fin);
		return -2;
	}
	if ((fout = fopen("output.txt","w")) == NULL)
	{
		printf("INVALID OUTPUT FILE");
		fclose(ans);
		fclose(fin);
		return -3;
	}
	if ((answers = (double*) malloc(m * sizeof(double))) == NULL)
	{
		printf("MEMORY ALLOCATION ERROR");
		fclose(fin);
		fclose(ans);
		fclose(fout);
		return -4;
	}
	for(i = 0; i < m; i++)
	{
		if (fscanf(fin, "%lf", &answers[i]) != 1)
		{
			fclose(fin);
			fclose(ans);
			fclose(fout);
			return -5;
		}
	}
	if (fscanf(fin, "%lf", &epsilon) != 1)
	{
		fclose(fin);
		fclose(ans);
		fclose(fout);
		return -6;
	}
	if (fscanf(fin, "%lf %lf", &a, &b) != 2)
	{
		fclose(fin);
		fclose(ans);
		fclose(fout);
		free(answers);
		return -7;
	}
	for(i = 0; i < m; i++)
	{
		result = integrate(a, b, epsilon, funcs[i]);
		if (result == answers[i])
		{
			fprintf(fout, "Test № %d: OK\n", (i + 1));
		}
		else
		{
			fprintf(fout, "Test № %d: LOSS\n", (i + 1));
			fclose(fin);
			fclose(ans);
			fclose(fout);
			free(answers);
			return -8;
		}
	}
	fclose(fin);
	fclose(ans);
	fclose(fout);
	free(answers);
	return 0;
}
double first(double x)
{
	return (x *(x + 2)) * 3;
}
