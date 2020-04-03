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

int main()
{
	FILE *fin, *fout, *ans;
	int i, m;
	double a, b, epsilon, *answers;
	struct result answer;
	struct otrezok *otrezoks;
	RRFUN funcs[] = {first, second, third, fourth, fifth, sixth};
	m = 6;
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
		answer = integrate(otrezoks[i].leftend, otrezoks[i].rightend, epsilon, funcs[i]);
		if (answer.n >= 1000000000)
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
		if (fabs(answer.rofi - answers[i]) <= epsilon * MAXOF3(answer.rofi, answers[i], 1))
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
