#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "minimum.h"

#define MAXOF2(x, y) (((x) > (y))?(x):(y))
#define MAXOF3(x, y, z) MAXOF2(x, MAXOF2(y, z))

struct otrezok
{
	double rightend;
	double leftend;
};

double first(double x);
double second(double x);
double third(double x);
double fourth(double x);
double fifth(double x);

int main ()
{
	FILE *fin, *fout, *ans;
	int i, m;
	double a, b, epsilon, *answers;
	double answer;
	ErrorCode eofm; //error_of_minimslisation
	struct otrezok *otrezoks;
	RRFUN funcs[] = {first, second, third, fourth, fifth};
	m = 5;
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
		answer = setka(funcs[i], epsilon, otrezoks[i].leftend, otrezoks[i].rightend, &eofm);
		fprintf(fout, "Test № %d: ", (i  + 1));
		if (eofm == MIN_NEOK)
		{
			fprintf(fout, "LOSS | Impossible to reach the defined accuracy\n");
			fclose(fin);
			fclose(ans);
			fclose(fout);
			free(answers);
			free(otrezoks);
			return -1;
		}
		if (fabs(answer - answers[i]) >= MAXOF3(answer, answers[i], 1) * epsilon)
		{
			fprintf(fout, "LOSS | Calculated value: %lf, Exact value: %lf, Error value: %lf\n", answer, answers[i], fabs(answer - answers[i]));
			fclose(fin);
			fclose(ans);
			fclose(fout);
			free(answers);
			free(otrezoks);
			return -1;
		}
		else
		{
			fprintf(fout, "OK | Calculated value: %lf, Exact value: %lf, Error value: %lf\n", answer, answers[i], fabs(answer - answers[i]));
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
	return x * x * log(x);
}
double second(double x)
{
	return x;
}
double third(double x)
{
	return sin(x);
}
double fourth(double x)
{
	return log(x) * cos(x);
}
double fifth(double x)
{
	return sin(x) * sqrt(3.141592653 * 2.718281828);
}



