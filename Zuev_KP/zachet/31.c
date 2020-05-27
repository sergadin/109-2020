#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
char *read_string(FILE *f);
char ***vbr(FILE *input1, int n_rows, int n_cols, char ***matrix);
int length(const char *s);
char *strcpy(char *t, const char *s);
int strst(char * t, char *w);
void delete(int i, char **mas, int n);

int strst(char * t, char *w) 
{
	int n;
	n = length(w);
	if(n > length(t))
		return 0;
	int i, j = 0;
	int p = 0, l = 0;
	l = length(t);
	for(i = 0; i < l - n; i++) 
	{
		p = 0;
		j = 0;
		while((t[i + j] == w[j]) && (j < n-1))
		{
			j = j+1;	
			p = p+1;
		}
		if(p+1 == n)
		{
			return 1;
		}
	}
	return 0;	
}

char *strcpy(char *t, const char *s) 
{
	int n, i; 
	n = length(s);
	for (i = 0; i < n+1; i++) 
	{
		t[i] = s[i];
	}
	return t;
}

int length(const char *s) 
{
	int n = 0;
	while (s[n] != '\0') 
	{
		n = n+1;
	}	
	return n;
}

char *read_string(FILE *f) 
{
	int l = 0, l1 = 0;	
	char *result;
	char buf[1024];	
	char *s = fgets(buf, 1024, f);
	if(!s) 
		return NULL;
	else
	{
		l = length(s);
		l1 = 0;
		result = (char*) malloc((l + 1)*sizeof(char));
		while(s)
		{
			strcpy(result+l1, s);
			if(s[length(s)-1] == '\n') 
				break;
			s = fgets(buf, 1024, f);
			if (s) 
			{
				l1 = length(s);
				l = l+l1;
				result = (char*) realloc(result, l+1);
			}
		} 
		return result;
	} 
}

void delete(int i, char **mas, int n)
{
	int j, k;
	for(j = i; j < n - 1; j++)
	{
		free(mas[j]);
		mas[j] = malloc(length(mas[j+1])+1);
		for(k = 0; k <= length(mas[j+1]); k++)
		{
			mas[j][k] = mas[j + 1][k];
		}
	}
	free(mas[n - 1]);
}

char ***vbr(FILE *input1, int n_rows, int n_cols, char ***matrix)
{
	int i, j, row, k = 0, l = 0, ind = 0, n;
	int w = 0;
	char *s;
	for(i = 0; i < n_rows; i ++)
        {
		l = 0;
                for(j = 0; j < n_cols; j ++)
                {
			l = l+length(mas[i][j]);
			if (length(mas[i][j])>=length(mas[i][n_cols-1-j]))
			{
			while(k < length(mas[i][j]))
			{
				n = 0;
		        	while (mas[i][j][k] == mas[i][n_cols-1-j][length(mas[i][n_cols-1-j])-1-n])
				{
				k = k+1;
				w = w+1;
				n = n+1;
				}
				k = k+1;
				if (w == length(mas[i][n_cols-1-j]))
				{
					ind = 1;
					break;
				}
				w = 0;
			}
			}
			if (ind = 1)
			{
				break;
			}
                }
		if (ind = 1)
		{
			break;
		}
        }
	w = 0;
	s = (char*) malloc((l)*sizeof(char));
	for(i = 0; i < n_rows; i ++)
        {
                for(j = 0; j < n_cols; j ++)
                {
			for(k = 0; k < length(mas[i][j]); k ++)
                	{
				while (w<l)
				{
					if(mas[i][j][k] == s[k])
					{
					 delete(k, mas[i], length(mas[i][j]));	
					}
					w = w+1;
				}
				w = 0;
			}			
		}
	}
	return mas;
}











int main(void)
{
	int row, i, j, n_rows, n_cols, l;
	char ***mas;
	FILE *input1, *result;
	if ((input1 = fopen("input1.txt", "r")) == NULL)
	{
		return -1;
	}
	if ((result = fopen("result.txt", "w")) == NULL)
	{
		return -1;
	}
	if (fscanf(input1, "%d", &n_rows)!=1)
	{
		return -1;
	}
	if (fscanf(input1, "%d", &n_cols)!=1)
	{
		return -1;
	}
	if (n_rows < 1)
	{
		return -1;
	}
	if (n_cols < 1) 
	{
		return -1;
	}
	mas = malloc(n_rows* sizeof(char **));
	if(mas == NULL)
		return -1;

	for(row = 0; row < n_rows; row ++)
	{
		mas[row] = malloc(n_cols * sizeof(char *));
		if(mas[row] == NULL)
			return -1;
	}
	for(i = 0; i < n_rows; i ++)
        {
                for(j = 0; j < n_cols; j ++)
                {
                        mas[i][j] = read_string(input1);
			l = length(mas[i][j]);
			mas[i][j] = realloc(mas[i][j], l);
			mas[i][j][l - 1] = '\0';
                }
        }

	mas = vbr(input1, n_rows, n_cols, mas);

	for(int i = 0; i < n_rows; i ++)
        {
                for(int j = 0; j < n_cols; j ++)
                {
                        fprintf(result, "%s\n", mas[i][j]);
                }

        }
	fclose(input1);
	fclose(result);
	return 0;	
}

