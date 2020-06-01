#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ftw.h>

#include "tree.h"

static int n, maxdepth;
static char **FL; //FL = File_List
static int *Levels;

void make_tree(char *directory, FILE *fout)
{
	maxdepth = 1;
	FL = (char**)malloc(0);
	Levels = (int*)malloc(sizeof(int));
	Levels[0] = 0;
	ftw(directory, fn, 20);
	qsort(FL, n, sizeof(char*), comp);
	count_tree(directory, 1);
	fprintf(fout, "%s", directory);
	print_tree(directory, fout, strlen(directory), 1);
	for (int i = 0; i < n; i++)
	{
		free(FL[i]);
	}
	free(FL);
	free(Levels);
}

int comp(const void *arg1, const void *arg2)
{
	const char *aa = *(const char**)arg1;
	const char *bb = *(const char**)arg2;
	return strcmp(aa, bb);
}

void count_tree(char *directory, int depth)
{
	char **SD; //SD = SubDirectories
	char *dir;
	int sdbi = 0, sdei = 0, cosd = 0, mem, lotlsd = 0;
	/* sdbi = SubDirectory_Beginning_Index
	   sdei = SubDirectory_Ending_Index
	   cosd = Count_Of_SubDirectories
	   mem = MEMory
	   lotlsd = Length_Of_The_Longest_SubDirectory
	   */
	SD = NULL;
	for (int i = 0; i < n; i++)
	{
		if (strstr(FL[i], directory) != NULL)
		{
			sdbi = strlen(directory) + 1;
			for (int j = sdbi; j < strlen(FL[i]); j++)
			{
				if (FL[i][j] == '/')
				{
					sdei = j - 1;
					break;
				}
			}
			if (sdei != 0)
			{
				cosd++;
				SD = (char**)realloc(SD, cosd * sizeof(char*));
				SD[cosd - 1] = (char*)malloc(sdei - sdbi + 2);
				for (int j = 0; j < sdei - sdbi + 1; j++)
				{
					SD[cosd - 1][j] = FL[i][sdbi + j];
				}
				SD[cosd - 1][sdei - sdbi + 1] = '\0';
			}
			sdei = 0;
		}
	}
	mem = cosd;
	for (int i = 0; i < cosd - 1; i++)
	{
		if (strcmp(SD[i], SD[i + 1]) == 0)
		{
			for (int j = i; j < cosd - 1; j++)
			{
				free(SD[j]);
				SD[j] = (char*)malloc(strlen(SD[j + 1]) + 1);
				strcpy(SD[j], SD[j + 1]);
			}
			cosd--;
			i--;
		}
	}
	for (int i = 0; i < cosd; i++)
	{
		if (strlen(SD[i]) > lotlsd)
		{
			lotlsd = strlen(SD[i]);
		}
	}
	if (maxdepth < depth)
	{
		Levels = (int*)realloc(Levels, depth * sizeof(int));
		Levels[depth - 1] = lotlsd;
		maxdepth = depth;
	}
	else
	{
		if(Levels[depth - 1] < lotlsd)
		{
			Levels[depth - 1] = lotlsd;
		}
	}
	if (cosd != 0)
	{
		for (int i = 0; i < cosd; i++)
		{
			dir = (char*)malloc(strlen(directory) + strlen(SD[i]) + 2);
			for (int j = 0; j < strlen(directory); j++)
			{
				dir[j] = directory[j];
			}
			dir[strlen(directory)] = '/';
			for (int j = 0; j < strlen(SD[i]); j++)
			{
				dir[strlen(directory) + 1 + j] = SD[i][j];
			}
			dir[strlen(directory) + strlen(SD[i]) + 1] = '\0';
			count_tree(dir, depth + 1);
			free(dir);
		}
	}
	for (int i = 0; i < mem; i++)
	{
		free(SD[i]);
	}
	free(SD);
}

void print_tree(char *directory, FILE *fout, int cs, int depth)
{
	char **SD; //SD = SubDirectories
	char *dir;
	int sdbi = 0, sdei = 0, cosd = 0, mem;
	/* sdbi = SubDirectory_Beginning_Index
	   sdei = SubDirectory_Ending_Index
	   cosd = Count_Of_SubDirectories
	   mem = MEMory
	   */
	SD = NULL;
	for (int i = 0; i < n; i++)
	{
		if (strstr(FL[i], directory) != NULL)
		{
			sdbi = strlen(directory) + 1;
			for (int j = sdbi; j < strlen(FL[i]); j++)
			{
				if (FL[i][j] == '/')
				{
					sdei = j - 1;
					break;
				}
			}
			if (sdei != 0)
			{
				cosd++;
				SD = (char**)realloc(SD, cosd * sizeof(char*));
				SD[cosd - 1] = (char*)malloc(sdei - sdbi + 2);
				for (int j = 0; j < sdei - sdbi + 1; j++)
				{
					SD[cosd - 1][j] = FL[i][sdbi + j];
				}
				SD[cosd - 1][sdei - sdbi + 1] = '\0';
			}
			sdei = 0;
		}
	}
	mem = cosd;
	for (int i = 0; i < cosd - 1; i++)
	{
		if (strcmp(SD[i], SD[i + 1]) == 0)
		{
			for (int j = i; j < cosd - 1; j++)
			{
				free(SD[j]);
				SD[j] = (char*)malloc(strlen(SD[j + 1]) + 1);
				strcpy(SD[j], SD[j + 1]);
			}
			cosd--;
			i--;
		}
	}
	if (cosd != 0)
	{
		for (int i = 0; i < cosd; i++)
		{
			if (i == 0)
			{
				fprintf(fout, " ——— ");
			}
			else
			{
				for (int j = 0; j < cs; j++)
				{
					fprintf (fout, " ");
				}
				fprintf(fout, "  |- ");
			}
			for (int j = 0; j < (Levels[depth - 1] - strlen(SD[i]))/2; j++)
			{
				fprintf (fout, " ");
			}
			if ((Levels[depth - 1] - strlen(SD[i]))%2 != 0)
			{
				fprintf (fout, " ");
			}
			fprintf(fout, "%s", SD[i]);
			for (int j = 0; j < (Levels[depth - 1] - strlen(SD[i]))/2; j++)
			{
				fprintf (fout, " ");
			}
			dir = (char*)malloc(strlen(directory) + strlen(SD[i]) + 2);
			for (int j = 0; j < strlen(directory); j++)
			{
				dir[j] = directory[j];
			}
			dir[strlen(directory)] = '/';
			for (int j = 0; j < strlen(SD[i]); j++)
			{
				dir[strlen(directory) + 1 + j] = SD[i][j];
			}
			dir[strlen(directory) + strlen(SD[i]) + 1] = '\0';
			print_tree(dir, fout, cs + 5 + Levels[depth - 1], depth + 1);
			free(dir);
		}
	}
	else
	{
		fprintf(fout, "\n");
	}
	for (int i = 0; i < mem; i++)
	{
		free(SD[i]);
	}
	free(SD);
}

static int fn(const char *file, const struct stat *sb, int flag)
{
	if (flag == FTW_F)
	{
		FL = (char**)realloc(FL, (n + 1) * sizeof(char*));
		FL[n] = NULL;
		FL[n] = realloc(FL[n], strlen(file) + 2);
		strcpy(FL[n], file);
		FL[n][strlen(file)] = '/';
		FL[n][strlen(file) + 1] = '\0';
		n++;
	}
	return 0;
}
