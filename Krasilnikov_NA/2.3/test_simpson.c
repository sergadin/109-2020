#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simpson.h"

#define MAXOF2(x, y) (((x) > (y))?(x):(y))
#define MAXOF3(x, y, z) MAXOF2(x, MAXOF2(y, z))

struct otrezok
{
	double leftend;
	double rightend;
};

double first(double x);
double second(double x);
double third(double x);
double fourth(double x);
double fifth(double x);
double sixth(double x);
double seventh(double x);
double eighth(double x);

int main()
{
	FILE *fin, *fout, *ans;
	int i, m;
	double a, b, epsilon, *answers;
	double answer;
	ErrorCode eofi; //error_of_integratio
	struct otrezok *otrezoks;
	RRFUN funcs[] = {first, second, third, fourth, fifth, sixth, seventh, eighth};
	m = 8;
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
			free(answers);
			return -1;
		}
	}
	if (fscanf(fin, "%lf", &epsilon) != 1)
	{
		fclose(fin);
		fclose(ans);
		fclose(fout);
		free(answers);
		return -1;
	}
	if ((otrezoks = (struct otrezok*) malloc(m * sizeof(struct otrezok))) == NULL)
	{
		fclose(fin);
		fclose(ans);
		fclose(fout);
		free(answers);
		return -1;
	}

	for (i = 0; i < m; i++)
	{
		if (fscanf(fin, "%lf %lf", &otrezoks[i].leftend, &otrezoks[i].rightend) != 2)
		{
			fclose(fin);
			fclose(ans);
			fclose(fout);
			free(answers);
			free(otrezoks);
			return -1;
		}
	}
	for(i = 0; i < m; i++)
	{
		answer = integrate(otrezoks[i].leftend, otrezoks[i].rightend, epsilon, funcs[i], &eofi);
		if (eofi == INT_NEOK)
		{
			fprintf(fout, "Test № %d: LOSS\n", (i + 1));
			fprintf(fout, "Impossible to calculate\n");
			fclose(fin);
			fclose(ans);
			fclose(fout);
			free(answers);
			free(otrezoks);
			return -1;
		}
		if (fabs(answer - answers[i]) <= epsilon * MAXOF3(answer, answers[i], 1))
		{
			fprintf(fout, "Test № %d: OK | ", (i + 1));
			fprintf(fout, "Calculated value: %lf | ", answer);
			fprintf(fout, "Exact value: %lf | ", answers[i]);
			fprintf(fout, "Error value: %lf\n", fabs(answer - answers[i]));

		}
		else
		{
			fprintf(fout, "Test № %d: LOSS\n", (i + 1));
			fclose(fin);
			fclose(ans);
			fclose(fout);
			free(answers);
			free(otrezoks);
			return -1;
		}
	}
	fclose(fin);
	fclose(ans);
	fclose(fout);
	free(answers);
	free(otrezoks);
	return 0;
}
double first(double x)
{
	return (x *(x + 2)) * (-3) - 7;
}
double second(double x)
{
	return sin(1/x);
}
double third(double x)
{
	return x;
}
double fourth(double x)
{
	return 0 * x;
}
double fifth(double x)
{
	return x * x;
}
double sixth(double x)
{
	return exp(x) * log(x);
}
double seventh(double x)
{
	return exp(1/(x + 0.05));
}
double eighth(double x)
{
	return sin(1/(x + 0.05) )*  exp(1/(x + 0.05));
}

