#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int n;
static int *a;	
static char **b;




/*int strlen(const char *s);
int strlen(const char *s) 
{
	int n = 0;
	while (s[n] != '\0') 
	{
		n = n+1;
	}	
	return n;
}*/
char *cop(char *t, const char *f);
char *cop(char *t, const char *f) 
{
	int n, i; 
	n = strlen(f);
	for (i = 0; i < n+1; i++) 
	{
		t[i] = f[i];
	}
	return t;
}
void sort(int *a, char **b, int n);
void sort(int *a, char **b, int n)
{
	int i, k, s;
	for(i = 1; i < n; i ++)
	{
		for(k = 1; k < n; k ++)
		{
			if(a[k] < a[k-1])
			{
				char *str = NULL;
				s = a[k];
				a[k] = a[k-1];
				a[k-1] = s;
				str = realloc(str, strlen(b[k]) + 1);
				str = cop(str, b[k]);
				b[k] = realloc(b[k], strlen(b[k-1]) + 1);
				b[k] = cop(b[k], b[k-1]);
				b[k-1] = realloc(b[k-1], strlen(str) + 1);
				b[k-1] = cop(b[k-1], str);
				free(str);
			}
		}
	}
}
int filesize(const char* file_name);
int filesize(const char* file_name)
{
	int size = 0;
	FILE* f = fopen(file_name, "rb"); 
	if(f == NULL)
	{
		size = -1;
	}
	else
{
		while(getc(f) != EOF)
			size++;
		fclose(f);
	}
	return size;
}

static int find(const char *file, const struct stat *sb, int flag) 
{
	int i;
	int size;
	if (flag == FTW_F) 
	{
			size = filesize(file);
			n = n + 1;
			a = realloc(a, (n)* sizeof(int *));
			b = realloc(b, (n)* sizeof(char *));
			b[n - 1] = NULL;
			b[n - 1] = realloc(b[n - 1], strlen(file) + 1);
			cop(b[n-1], file); 
			a[n-1] = size;
	}
	return 0;         
}

int main(int argc, char *argv[]) 
{
	int i;
	n = 0;
	a = (int*) malloc(0 * sizeof(int));
	b = malloc(0* sizeof(char));
	if (argc == 1 || argc >= 3) 
	{
		printf("ERROR\n");
        return 0;
    }
	if (argc == 2) 
	{
		ftw(argv[1], find, 20);
	} 
	sort(a, b, n);
	for (i = 0; i<n; i++)
	{
		printf("%d\n", a[i]);
		printf("%s\n", b[i]);
	}
	for (i = 0; i<n; i++)
	{
		free(b[i]);
	}
	free(a);
	free(b);
	return 0;
}

