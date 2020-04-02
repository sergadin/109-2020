#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simpson.h"

#define MAXOF2(x, y) (((x) > (y))?(x):(y))
#define MAXOF3(x, y, z) MAXOF2(x, MAXOF2(y, z))

double first(double x);
double second(double x);

int main()
{
	FILE *fin, *fout, *ans;
	int i, m;
	double a, b, epsilon, *answers;
  struct result answer;
	RRFUN funcs[] = {first, second};
	m = 2;
	if ((fin = fopen("input.txt","r")) == NULL)
	{
		printf("INVALID INPUT FILE");
		return -1;
	}
	if ((ans = fopen("answers.txt","r")) == NULL)
	{
		printf("INVALID ANSWERS FILE");
		fclose(fin);
		return -1;
	}
	if ((fout = fopen("output.txt","w")) == NULL)
	{
		printf("INVALID OUTPUT FILE");
		fclose(ans);
		fclose(fin);
		return -1;
	}
	if ((answers = (double*) malloc(m * sizeof(double))) == NULL)
	{
		printf("MEMORY ALLOCATION ERROR");
		fclose(fin);
		fclose(ans);
		fclose(fout);
		return -1;
	}
	for(i = 0; i < m; i++)
	{
		if (fscanf(ans, "%lf", &answers[i]) != 1)
		{
			fclose(fin);
			fclose(ans);
			fclose(fout);
			return -1;
		}
	}
	if (fscanf(fin, "%lf", &epsilon) != 1)
	{
		fclose(fin);
		fclose(ans);
		fclose(fout);
		return -1;
	}
	if (fscanf(fin, "%lf %lf", &a, &b) != 2)
	{
		fclose(fin);
		fclose(ans);
		fclose(fout);
		free(answers);
		return -1;
	}
	for(i = 0; i < m; i++)
	{
		answer.rofi = integrate(a, b, epsilon, funcs[i]);
    if (answer.n >= 1000000000)
    {
      fprintf(fout, "Test № %d: LOSS\n", (i + 1));
      fprintf(fout, "Impossible to calculate\n");
      fclose(fin);
      fclose(ans);
      fclose(fout);
      free(answers);
      return -1;
    }
		if (fabs(answer.rofi - answers[i]) < epsilon * MAXOF3(answer.rofi, answers[i], 1))
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
			return -1;
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
	return (x *(x + 2)) * 3 - 7;
}
double second(double x)
{
	return sin(1/x);
}
