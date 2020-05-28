#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

char * zam(char * st, char * s);
char *readstring(FILE * input);
char *** func(char *** matrix, int nrows, int ncols);
int len(const char *s);
char *strcpy(char *t, const char *s);
char * obr(char * str);
int findstr(char * t, const  char *w);

int findstr(char * t, const  char *w) 
{
	if(len(w) > len(t))
		return 0;
	int i, j = 0;
	int p = 0, le = 0;
	int n1 = 0;
	le = len(t);
	n1 = len(w);
	for(i = 0; i < le - n1 + 1; i++) 
	{
		p = 0;
		j = 0;
		while((t[i + j] == w[j]) && (j < n1))
		{
			j++;	
			p = p + 1;
		}
		if(p == n1)
		{
			return i;
		}
		
	}
	return 0;	
}	
int len(const char *s)
{
        int n = 0;
        while (*s++)
        {
                n++;
        }
        return n;
}

char *strcpy(char *t, const char *s)
{
        int n;
        n = len(s);
        for (int i = 0; i < n + 1; i++)
        {
                t[i] = s[i];
        }
        return t;
}


char ***func(char *** matrix, int nrows, int ncols)//osnovnaya funkci
{
	char * str;
	int ind = 0;
	int prev;
	int lenn = 0;
	int i = -1;
	int numstr = 0;
	while((ind == 0) && (i <= nrows - 2))//poka ne vstretily nygnuyu stroky ili ne vyshli za granicy
	{
		i ++;
		ind = 0;
		str = malloc(1);//skleennaya stroka
		prev = len(matrix[i][0]); 
		lenn = len(matrix[i][0]);
		for(int j = 1; j < ncols; j ++)
		{			
			matrix[i][0] = realloc(matrix[i][0], lenn + len(matrix[i][j]));
			lenn += len(matrix[i][j]);
			for(int k = 0; k < len(matrix[i][j]); k++)
			{
				str[prev + k] = matrix[i][j][k];

			}
			prev += len(matrix[i][j]);
		}
		str = realloc(str, lenn + 1);
		str[lenn] = '\0';
		str = obr(str);//obratily
		for(int j = 0; j < ncols; j ++)
		{
			if(strstr(str, matrix[i][j]) != NULL)//ishem elementy iz etoy stroki
			{
				ind = 1;
				printf("%s\n", str);
			}
		}
		free(str);
	}
	if(ind == 1)
	{
		numstr = i;
		for(i = 0; i < nrows; i ++)
		{
			if(i != numstr)
			{
				for(int j = 0; j < ncols; j ++)
				{
					matrix[i][j] = zam(matrix[numstr][j], matrix[i][j]);//zamenayem elemnt na nuzny
				}
			}
		}	


	}
	return matrix;
}
char * obr(char * str)//obrashayet stroku
{
	char * s = malloc(len(str) + 1);
	for(int i = 0; i < len(str); i++)
	{
		s[len(str) - 1 - i] = str[i];

	}
	s[len(str)] = '\0';
	str = strcpy(str, s);
	free(s);
	return str;
}

char * zam(char * st, char * s)// zamenayet elemnt kak v uslovii 4 (34)
{
	char * str = malloc(1);
	int lenn = 0;
	for(int i = 0; i < len(st); i ++)
	{
		if(strchr(s, st[i]) == NULL)//ishet bykvy kotoryh net v tekyshey stroke
		{
			str = realloc(str, lenn + 1);
			lenn ++;
			str[lenn - 1] = st[i];
		}
	}
	str = realloc(str, lenn + 1);
	str[lenn] = '\0';
	s = realloc(s, lenn + 1);
	s = strcpy(s, str);
	free(str);	
	return s;

}
char *readstring(FILE * input)
{
	int l, p = 0;
	char *res;
	char buf[1024];
	char *s;
	s = fgets(buf, 1024, input);
	if(s)
	{
		l = len(s);
		res = (char *) malloc((l + 1)*sizeof(char));
		strcpy(res, s);
		while((s) && (s[len(s) - 1] != '\n'))
		{
			strcpy(res, s);
			s = fgets(buf, 1024, input);
			if(s)
			{
				p = len(s);
				l += p;
		        	res = (char *) realloc(res, l);
			}
		
		}
		
		return res;
	}
	return NULL;
}


int main(void)
{
	printf("There must be two numbers at the beginning of the file: the total number of rows and the total number of columns in the matrix. The matrix should be written row by row. If the real size of the matrix in the file is less than the declared size, then the program will not work, if the real size is larger than the declared size, the program will display an incorrect answer. If there are extraneous symbols in the file in lines that fall within the boundaries of the declared size, the program will not work; if extraneous symbols follow the lines corresponding to the declared size, the program will correctly process the matrix specified in the file.");
	

	FILE *input, *output;
	char *** matrix;
        int nrows, ncols;
        int k;
	int len1;
	int lenn;
	double el;
        if((input = fopen("input.txt", "r")) == NULL)
		return -1;
        if((output = fopen("output.txt", "w")) == NULL)
        {
                fclose(input);
                return -1;
        }
	if(fscanf(input, "%d", &nrows) != 1)
	{
		fclose(input);
		fclose(output);
		return -1;
	}
	if(fscanf(input, "%d\n", &ncols) != 1)
        {
		fclose(input);
                fclose(output);
                return -1;
        }
	if((nrows <= 0) || (ncols <= 0))
	{
		fclose(input);
                fclose(output);
		return -1;
	}
	matrix = malloc(nrows* sizeof(char **));
	if(matrix == NULL)
		return -1;

	for(int row = 0; row < nrows; row ++)
	{
		matrix[row] = malloc(ncols * sizeof(char *));
		if(matrix[row] == NULL)
			return -1;
	}
	for(int i = 0; i < nrows; i ++)
        {
                for(int j = 0; j < ncols; j ++)
                {
                        matrix[i][j] = readstring(input);
			if(matrix[i][j] == NULL)
			{
				fclose(input);
				fclose(output);
				return -1;
			}
			lenn = len(matrix[i][j]);
			matrix[i][j] = realloc(matrix[i][j], lenn);
			matrix[i][j][lenn - 1] = '\0';
                }

        }
	matrix = func(matrix, nrows, ncols);

	for(int i = 0; i < nrows; i ++)
        {
                for(int j = 0; j < ncols; j ++)
                {
                        fprintf(output, "%s\n", matrix[i][j]);
                }

        }
	for(int i = 0; i < nrows; i ++)
	{
		for(int j = 0; j < ncols; j ++)
		{
			free(matrix[i][j]);
		}
		free(matrix[i]);
	}
	free(matrix);
	fclose(input);
	fclose(output);
}

