#include <stdio.h>
#include <math.h>
#include <stdlib.h>
char *read_string(FILE *f);
char *vbr(FILE *input1, int n_rows, int n_cols, char ***mas);
int length(const char *s);
char *strcpy(char *t, const char *s);
int strst(char * t, const char *w, int n);

int strst(char * t, const char *w, int n) 
{
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



char *vbr(FILE *input1, int n_rows, int n_cols, char ***mas)
{
	char *s;
	char *d = "a";
	int i, j, row, k, l;
	for(i = 0; i < n_rows; i ++)
        {
                for(j = 0; j < n_cols; j ++)
                {
			l = length(mas[i][j]);
			//printf("%d\n", l);
			s = (char*) malloc((l)*sizeof(char));
			for(k = 0; k < l; k ++)
                	{
		                s[l-1-k] = mas[i][j][k];
			}
			strcpy(mas[i][j], s);
			printf("%s\n", mas[i][j]);
                }
		printf("\n");
        }
	for(i = 0; i < n_rows; i++)
	{
		for(j = 0; j < n_cols; j++)
		{
			//if (strst(mas[i][j], d) != 0) 
			//s[i][j-n_cols-1] = mas[i][j];
			//printf("%s\n", mas[i][j]);
			
		}
	}
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


	vbr(input1, n_rows, n_cols, mas);
	










	fclose(input1);
	fclose(result);
	return 0;	
}

	/*mas = malloc(n_rows * sizeof(char**));
	if (mas == NULL)
		return -1;
	for(row = 0; row < n_rows; row++)
	{
		mas[row] = malloc(n_cols* sizeof(char *));
		if (mas[row] == NULL)
			return -1;
	}
	for(i = 0; i < n_rows ; i ++)
	{
		for(j = 0; j < n_cols; j ++)
		{
			mas[i][j] = read_string(input1);
		}
	}*/













