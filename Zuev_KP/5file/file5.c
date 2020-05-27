#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static const char *type;
int64_t filesize(const char* file_name);
int cmp(const void *a, const void *b);

int cmp(const void *a, const void *b) 
{
     return *(int*)a - *(int*)b;
}

//qsort(a, n, sizeof(int), cmp );

int64_t filesize(const char* file)
{
	long size = 0;
	FILE* f = fopen(file, "rb"); //"rb" открывает двоичный файл для чтения
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
	if (flag == FTW_F) 
	{
			long size;
			size = filesize(file);
			printf("%ld\n", size);
			strrchr(file, '/');
			printf("%s\n", file);
	}
	return 0;         
}

int main(int argc, char *argv[]) 
{
	if (argc == 2) 
	{
		type = argv[1];
		ftw(argv[1], check, 50);
	}  
	return 0;
}
