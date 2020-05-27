#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdint.h> // для int64_t
#include <inttypes.h> // для правильного вывода int64_t в printf

static int n;

int filesize(const char* file_name);
int cmp(const void *a, const void *b);

int cmp(const void *a, const void *b) 
{
     return *(int*)a - *(int*)b;
}

int filesize(const char* file_name)
{
	int size = 0;
	FILE* f = fopen(file_name, "rb"); //"rb" открывает двоичный файл для чтения
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

static int check(const char *file, const struct stat *sb, int flag) 
{
	int i;
	int size;
	int *a;	
	a = (int*) malloc(n * sizeof(int));
	if (flag == FTW_F) 
	{
			size = filesize(file);
			n = n+1;
			a = realloc(a, (n)* sizeof(int *));
			a[n-1] = size;
	}
	qsort(a, n, sizeof(int), cmp);
    	for(i = 0 ; i < n; i++) 
	{
        	printf("%d\n", a[i]);
    	}
	return 0;         
}

int main(int argc, char *argv[]) 
{
	int i;
	if (argc == 2) 
	{
		ftw(argv[1], check, 50);
	}  
	return 0;
}

