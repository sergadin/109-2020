#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "33.h"

void matrix_transformation(FILE *fin, FILE *fout)
{
	int p;
	char *memory;
	int keyrow = -1, crl, cook; //crl = Current_Row_Length
	struct matr matrix;
	matrix = matrix_reading(fin);
	switch(matrix.e)
	{
		case -1:
			fprintf(fout, "Invalid input format");
			break;
		case -2:
			fprintf(fout, "Memory allocation error");
			break;
		case 0:
			for (int i = 0; i < matrix.r; i++)
			{
				crl = 0;
				for (int j = 0; j < matrix.c; j++)
				{
					crl += slength(matrix.m[i][j]);
				}
				for (int j = 0; j < matrix.c; j++)
				{
					for (int k = crl - 1; k >= slength(matrix.m[i][j]) - 1; k--)
					{
						if (matrix.m[i][j][slength(matrix.m[i][j]) - 1] == sir(matrix.m[i], matrix.c, k))
						{
							cook = 0;
							for (int l = slength(matrix.m[i][j]) - 2,  p = 1; l >= 0; l--, p++)
							{
								if (matrix.m[i][j][l] == sir(matrix.m[i], matrix.c, k + p))
								{
									cook++;

								}
								else
								{
									break;
								}
							}
							if (cook == slength(matrix.m[i][j]) - 1)
							{
								keyrow = i;
							}
						}
					}
				}
				if (keyrow != -1)
				{
					break;
				}
			}
			if (keyrow != -1)
			{
				for (int i = 0; i < matrix.r; i++)
				{
					if (i != keyrow)
					{
						for (int j = 0; j < matrix.c; j++)
						{
							int length = slength(matrix.m[i][j]);
							if ((matrix.m[i][j] = (char*)realloc(matrix.m[i][j], slength(matrix.m[i][j]) + slength(matrix.m[keyrow][j]) + 1)) == NULL)
							{
								matrix.e = -2;
								break;
							}
							for (int k = 0; k <= slength(matrix.m[keyrow][j]); k++)
							{
								
								if (k != slength(matrix.m[keyrow][j]))
								{
									matrix.m[i][j][length + k] = matrix.m[keyrow][j][k];
								}
								else
								{
									matrix.m[i][j][length + k] = '\0';
								}
							}	

						}
						if (matrix.e == -2)
						{
							break;
						}
					}
				}
			}
			printmatr(matrix, fout);		
			free_2D(matrix);
			break;
	}
}

void printmatr(struct matr matrix, FILE *fout)
{
	for (int i = 0; i < matrix.r; i++)
	{
		for (int j = 0; j < matrix.c; j++)
		{
			fprintf(fout, "%s", matrix.m[i][j]);
			if (j != matrix.c - 1)
			{
				fprintf(fout, " ");
			}
		}
		if (i != matrix.r - 1)
		{
			fprintf(fout, "\n");
		}
		
	}
}

char sir (char** row, int cow, int number)
{
	for (int i = 0;  i < cow; i++)
	{
		if (number >= slength(row[i]))
		{
			number -= slength(row[i]);
		}
		else
		{
			return row[i][number];
		}
	}
}

void free_2D(struct matr matrix)
{
	for (int i = 0; i < matrix.r; i++)
	{
		for (int j = 0; j < matrix.c; j++)
		{
			free(matrix.m[i][j]);
		}
		free(matrix.m[i]);
	}
	free(matrix.m);
}	

struct matr matrix_reading(FILE *fin)
{
	int cr; // cr = Current_Row
	char *cs, *ms; // cs = Current_Stringi
	struct matr matrix;
	matrix.e = 0;
	if ((fscanf(fin, "%d", &matrix.r) != 1) || (matrix.r < 1))
	{
		matrix.e = -1;
		return matrix;
	}
	if ((fscanf(fin, "%d", &matrix.c) != 1) || (matrix.c < 1))
	{
		matrix.e = -1;
		return matrix;
	}
	if ((ms = (char*) malloc(2 *sizeof(char))) == NULL)
	{
		matrix.e = -2;
		return matrix;
	}
	fgets(ms, 2, fin);
	free(ms);
	if ((matrix.m = (char***) malloc(matrix.r * sizeof(char**))) == NULL)
	{
		matrix.e = -2;
		return matrix;
	}
	for (int i = 0; i < matrix.r; i++)
	{
		if ((matrix.m[i] = (char**) malloc(matrix.c * sizeof(char*))) == NULL)
		{
			for (int j = 0; j < i; j++)
			{
				free(matrix.m[j]);
			}
			free(matrix.m);
			matrix.e = -2;
			return matrix;
		}
	}
	for (int i = 0; i < matrix.r; i++)
	{
		for (int j = 0; j < matrix.c; j++)
		{
			if ((cs = sread(fin)) == NULL)
			{
				for (int k = 0; k < j; k++)
				{
					free(matrix.m[i][k]);
				}
				free(matrix.m[i]);
				for (int k = 0; k < i; k++)
				{
					for (int l = 0; l < matrix.c; l++)
					{
						free(matrix.m[i][l]);
					}
					free(matrix.m[k]);
				}
				free (matrix.m);
				matrix.e = -1;
				return matrix;
			}
			if ((matrix.m[i][j] = (char*)malloc((slength(cs) + 1) * sizeof(char))) == NULL)
			{
				for (int k = 0; k < j; k++)
				{
					free(matrix.m[i][k]);
				}
				free(matrix.m[i]);
				for (int k = 0; k < i; k++)
				{
					for (int l = 0; l < matrix.c; l++)
					{
						free(matrix.m[i][l]);
					}
					free(matrix.m[k]);
				}
				free (matrix.m);
				matrix.e = -2;
				return matrix;;
			}
			scopy(cs, matrix.m[i][j]);
			free(cs);
		}
	}
	return matrix;
}

int slength(const char *string)
{
	int length = 0;
	while (string[length] != '\0')
	{
		length ++;
	}
	return length;
}

char *scopy(const char *from, char *to)
{
	int length;
	length = slength(from);
	for (int i = 0; i <= length; i++)
	{
		to[i] = from[i];
	}
	return to;
}

char *sread(FILE *fin)
{
	int N = 1024, cl = 1, bl; //cl = Current_length, bl = Buf_length
	char *string, *buf;
	if ((buf = (char*)malloc(N)) == NULL)
	{
		return NULL;
	}
	if ((string = (char*)malloc(1)) == NULL)
	{
		free(buf);
		return NULL;
	}
	do
	{
		if (fgets(buf, N, fin) == NULL)
		{
			free(buf);
			free(string);
			return NULL;
		}
		bl = slength(buf);
		if ((string = (char*)realloc(string, cl + bl)) == NULL)
		{
			free(buf);
			free(string);
			return NULL;
		}
		scopy(buf, &string[cl - 1]);
		cl += bl;
		if ((cl > 1) && (string[cl - 2] == '\n'))
		{
			string[cl - 2] = '\0';
			if ((string = (char*)realloc(string, cl - 1)) == NULL)
			{
				free(buf);
				free(string);
				return NULL;
			}
			break;
		}
	}
	while (slength(buf) > 0);
	free(buf);
	return string;
}
