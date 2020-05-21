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
// первый элемент списка имеет вид List = {"название директории", 0, *}

struct chain *List1;
struct chain *List2;
char *dir1;
char *dir2;

/*
** Строит по полному адресу файла его название в последней директории:
** dir1/dir2/.../dirn/file -> file
** если имя файла или имя какой-то промежуточной директории оказалось пустым, возвращает 0
*/
char *file_name(const char *filename);
char *file_name(const char *filename)
{
	int i = 0;
	char *new_filename;
	if (strlen(filename) == 0)
		return 0;
	if (filename[0] == '/')
		return 0;
	while (i < strlen(filename))
	{
		if (filename[i] == '/')
			return file_name(filename + i + 1);
		i++;
	}
	if (i == strlen(filename))
	{
		new_filename = (char*)malloc((strlen(filename) + 1) * sizeof(char));
		return strcpy(new_filename, filename);
	}
}

/*
** Запись имени файла в последней директории в список файлов
** filename - полное имя записываемого файла
** filelist - указатель на начало списка
** Если в списке filelist нет элемента с именем file_name(filename), происходит запись в конец списка
** Если в списке filelist есть элемент с именем file_name(filename), не происходит ничего
*/
int write_in_filelist(const char *filename, struct chain *filelist);
int write_in_filelist(const char *filename, struct chain *filelist)
{
	struct chain *new_file;
	char *new_filename;
	new_filename = (char*)malloc((strlen(filename) + 1) * sizeof(char));
	new_filename = filename;
	new_file = filelist->next;
	while(new_file != 0)
	{
		if (new_file->name == new_filename)
		{
			free(new_filename);
			return 0;
		}
		new_file = new_file->next;
	}
	new_file = (struct chain*)malloc(sizeof(struct chain));
	new_file->name = new_filename;
	new_file->next = filelist->next;
	new_file->prev = filelist;
	filelist->next = new_file;
}



/*int find_file_in_list(char *filename, struct chain *filelist)
{
	struct chain *FL;
	FL = filelist;
	while(FL != 0)
	{
		
	}
}*/

int func_for_ftw(const char *fpath, const struct stat *sb, int flag);
int func_for_ftw(const char *fpath, const struct stat *sb, int flag)
{
	if (flag == FTW_F)
	{
		if (strlen(fpath) >= strlen(dir1))
			if (strncmp(fpath, dir1, strlen(dir1)) == 0)
				write_in_filelist(fpath, List1);
		if (strlen(fpath) >= strlen(dir2))
			if (strncmp(fpath, dir2, strlen(dir2)) == 0)
				write_in_filelist(fpath, List2);
	}
	return 0;
}

int main(void)
{
	dir1 = (char*)malloc((strlen("dir1") + 1) * sizeof(char));
	strcpy(dir1, "dir1");
	dir2 = (char*)malloc((strlen("dir2") + 1) * sizeof(char));
	strcpy(dir2, "dir2");
	
	List1 = (struct chain*)malloc(sizeof(struct chain));
	List1->name = (char*)malloc((strlen(dir1) + 1) * sizeof(char));
	strcpy(List1->name, dir1);
	List1->next = List1->prev = 0;
	
	List2 = (struct chain*)malloc(sizeof(struct chain));
	List2->name = (char*)malloc((strlen(dir2) + 1) * sizeof(char));
	strcpy(List2->name, dir2);
	List2->next = List2->prev = 0;
	
	ftw(dir1, func_for_ftw, 20);
	while (1)
	{
		printf("%s\n", List1->name);
		free(List1->name);
		if (List1->next != 0)
		{
			List1 = List1->next;
			free(List1->prev);
		}
		else
		{
			free(List1);
			break;
		}
	}
	
	ftw(dir2, func_for_ftw, 20);
	while (1)
	{
		printf("%s\n", List2->name);
		free(List2->name);
		if (List2->next != 0)
		{
			List2 = List2->next;
			free(List2->prev);
		}
		else
		{
			free(List2);
			break;
		}
	}
	free(dir1);
	free(dir2);
	return 0;
}
