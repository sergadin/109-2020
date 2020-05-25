#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ftw.h>
#include <sys/stat.h>
#include<math.h>
	
char **Mass_of_filenames;
int count_names = 0;
/*
	Функция Names вызывается из функции ftw для первой директории
	
	Параметры:
	 * fpath: путь к файлу (или директории)
	 * sb: указатель на структуру, содержащую основную информацию о файле
	 * typeflag: целочисленное значение, обозначающее тип файла
	Если по заданному в fpath адресу находится файл, то он отделяется от своего полного адреса и 
	в двумерный массив имен добавляется одна новая ячейка, в которую заносится имя этого файла.
*/
static int Names(const char *fpath, const struct stat *sb, int typeflag)
{
	if (typeflag == FTW_D)
		return 0;

	if (typeflag == FTW_F)
    {	
		char *filename;

		if (strrchr(fpath, '/') != NULL)
		{
			filename = strrchr(fpath, '/');
			Mass_of_filenames = realloc(Mass_of_filenames, (count_names + 1)* sizeof(char*));
			Mass_of_filenames[count_names] = malloc(strlen(filename)+1 * sizeof(char));
			strcpy(Mass_of_filenames[count_names], filename);
			count_names++;
		}
	}
	return 0;
}
/*
	Функция Compare вызывается из функции ftw для второй директории
	
	Параметры:
	 * fpath: путь к файлу (или директории)
	 * sb: указатель на структуру, содержащую основную информацию о файле
	 * typeflag: целочисленное значение, обозначающее тип файла
	 
	Если по заданному в fpath адресу находится файл, то он отделяется от своего полного адреса
	и сравнивается с каждым именем в массиве имён первой директории
*/

static int Compare(const char *fpath, const struct stat *sb, int typeflag)
{
	int NameIn = 0;
	if (typeflag == FTW_D) {
		return 0;
	}
	if (typeflag == FTW_F)
    {	
		char *filename;
		if (strrchr(fpath, '/') != NULL)
		{
			filename = strrchr(fpath, '/');
			for (int i = 0; i < count_names; i++)
			{
				if (strstr(Mass_of_filenames[i], filename))
				{
					NameIn = 1;
					break;
				}
			}
		}
		if (NameIn == 1)
			printf("%s\n", filename);
	}
	return 0;
}


int main(int argc, char **argv)
{
	int result;
	char *Catalog1, *Catalog2;
	
	if (argc != 3)
	{
		printf("usage:Dir1 Dir2\n", argv[0]);
		return 1;
	}
	Catalog1 = argv[1];
	Catalog2 = argv[2];
 
	ftw(argv[1], Names, 10);
	ftw(argv[2], Compare, 10);
	
	return 0;
}