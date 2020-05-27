#include <stdio.h>
#include <stdlib.h>

void matrix_transformation(FILE *fin, FILE *fout, ErrorCode *ma)
{
  *ma = MATRIX_OK;
  char ***matrix;
  int rows, columns;
  if (matrix_reading(fin, matrix, rows, columns) != 0)
  {
    printf("kek");
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      printf ("%s " matrix[i][j]);
    }
    printf("\n");
  }
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      free(matrix[i][j]);
    }
    free(matrix[i]);
  }
  free(matrix);
  }
}

int matrix_reading(FILE *fin, char ***matrix, int rows, int columns)
{
  int cr; // cr = Current_Row
  char *cs; // cs = Current_String
  if (fscanf(fin, "%d %d", &rows, &columns) != 2)
  {
    return -1;
  }
  if ((matrix = (char***) malloc(rows * sizeof(char**))) == NULL)
  {
    return -2;
  }
  for (int i = 0; i < rows; i++)
  {
    if ((matrix[i] = (char**) malloc(columns * sizeof(char**))) == NULL)
    {
      for (int j = 0; j < i; j++)
      {
        free(matrix[j]);
      }
      free(matrix);
      return -2;
    }
  }
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      if ((cs = sread(fin)) == NULL)
      {
        for (int k = 0; k < j; k++)
        {
          free(matrix[i][k]);
        }
        free(matrix[i]);
        for (int k = 0; k < i; k++)
        {
          for (int l = 0; l < columns; l++)
          {
            free(matrix[i][l]);
          }
          free(matrix[k]);
        }
        free (matrix);
        return -1;
      }
      if ((matrix[i][j] = (char*)malloc((slength(cs) + 1) * sizeof(char*))) == NULL)
      {
        for (int k = 0; k < j; k++)
        {
          free(matrix[i][k]);
        }
        free(matrix[i]);
        for (int k = 0; k < i; k++)
        {
          for (int l = 0; l < columns; l++)
          {
            free(matrix[i][l]);
          }
          free(matrix[k]);
        }
        free (matrix);
        return -2;
      }
      scopy(sc, matrix[i][j]);
      free(sc);
    }
  }
  return 0;
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
