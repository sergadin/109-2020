#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ftw.h>

struct chain // реализация списка файлов
{
	char *name;         // имя файла 
	struct chain *next; // указатель на следующий файл в списке
	                    // если следующего нет, то 0
	struct chain *prev; // указатель на предыдущий файл в списке
	                    // если предыдущего нет, то 0
};

struct chain *List1;
struct chain *List2;
char *dir1;
char *dir2;

/*
** Строит по полному адресу файла его название в последней директории:
** dir1/dir2/.../dirn/file -> file
*/
char *file_name(const char *filename);
char *file_name(const char *filename)
{
	int i = strlen(filename);
	char *new_filename;
	while((i >= 0) && (filename[i] != '/'))
		i--;
	new_filename = (char*)malloc((strlen(filename) - i) * sizeof(char));
	strcpy(new_filename, filename + i + 1);
	return new_filename;
}

/*
** Запись файла в список файлов
** filename - имя записываемого файла
** filelist - указатель на первый элемент списка
** Если в списке filelist нет элемента с именем file_name(filename), то такой элемент добавляется в конец списка
** Если в списке filelist есть элемент с именем file_name(filename), то не происходит ничего
*/
int write_in_filelist(const char *filename, struct chain *filelist);
int write_in_filelist(const char *filename, struct chain *filelist)
{
	struct chain *new_file;
	char *new_filename;
	struct chain *last_file;
	new_filename = file_name(filename);
	last_file = filelist;
	while(last_file->next != 0)
	{
		if (strcmp(last_file->next->name, new_filename) == 0)
		{
			free(new_filename);
			return 0;
		}
		last_file = last_file->next;
	}
	
	new_file = (struct chain*)malloc(sizeof(struct chain));
	new_file->name = new_filename;
	new_file->next = 0;
	new_file->prev = last_file;
	last_file->next = new_file;
	return 0;
}

/*
** Находит файл filename в списке filelist
** short_filename - имя искомого файла
** filelist - указатель на первый элемент списка
** функция возвращает 1, если файл есть в списке и 0 иначе
*/
int find_file_in_list(char *short_filename, struct chain *filelist);
int find_file_in_list(char *short_filename, struct chain *filelist)
{
	struct chain *FL;
	FL = filelist;
	while(FL != 0)
	{
		if (strcmp(FL->name, short_filename) == 0)
			return 1;
		FL = FL->next;
	}
	return 0;
}

int func_for_ftw(const char *fpath, const struct stat *sb, int flag);
int func_for_ftw(const char *fpath, const struct stat *sb, int flag)
{
	if (flag == FTW_F)
	{
		if (strncmp(fpath, dir1, strlen(dir1)) == 0)
		{
			write_in_filelist(fpath, List1);
		}
		if (strncmp(fpath, dir2, strlen(dir2)) == 0)
		{
			write_in_filelist(fpath, List2);
		}
	}
	return 0;
}

int main (int argc, const char **argv)
{
	if (argc != 3)
		return -1;
	dir1 = (char*)malloc((strlen("dir1") + 1) * sizeof(char));
	strcpy(dir1, argv[1]);
	dir2 = (char*)malloc((strlen("dir2") + 1) * sizeof(char));
	strcpy(dir2, argv[2]);
	
	List1 = (struct chain*)malloc(sizeof(struct chain));
	List1->name = (char*)malloc((strlen(dir1) + 1) * sizeof(char));
	strcpy(List1->name, dir1);
	List1->next = List1->prev = 0;
	
	List2 = (struct chain*)malloc(sizeof(struct chain));
	List2->name = (char*)malloc((strlen(dir2) + 1) * sizeof(char));
	strcpy(List2->name, dir2);
	List2->next = List2->prev = 0;
	
	ftw(dir1, func_for_ftw, 20);
	ftw(dir2, func_for_ftw, 20);
	
	printf("Файлы, присутствующие в %s, но отсутсвующие в %s:\n", dir1, dir2);
	for (struct chain *FL = List1->next; FL != 0; FL = FL->next)
	{
		if (find_file_in_list(FL->name, List2) == 0)
		    printf("%s\n", FL->name);
	}
	
	printf("Файлы, присутствующие в %s, но отсутсвующие в %s:\n", dir2, dir1);
	for (struct chain *FL = List2->next; FL != 0; FL = FL->next)
	{
		if (find_file_in_list(FL->name, List1) == 0)
		    printf("%s\n", FL->name);
	}
	
	while (List1 != 0)
	{
		struct chain *next;
		next = List1->next;
		free(List1->name);
		free(List1);
		List1 = next;
	}
	while (List2 != 0)
	{
		struct chain *next;
		next = List2->next;
		free(List2->name);
		free(List2);
		List2 = next;
	}

	free(dir1);
	free(dir2);
	return 0;
}
