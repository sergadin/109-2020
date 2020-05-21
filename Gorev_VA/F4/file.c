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

/*
** Строит по полному адресу файла его название в последней директории:
** dir1/dir2/.../dirn/file -> file
** если имя файла или имя какой-то промежуточной директории оказалось пустым, возвращает 0
*/
char *file_name(char *filename);
char *file_name(char *filename)
{
	int i = 0;
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
		return filename;
}

/*
** Запись файла в список файлов
** filename - имя записываемого файла
** filelist - указатель на какой-то элемент списка
** создается элемент chain между filelist и filelist->next
*/
void write_in_filelist(char *filename, struct chain *filelist);
void write_in_filelist(char *filename, struct chain *filelist)
{
	struct chain *new_file;
	new_file = (struct chain*)malloc(sizeof(struct chain));
	new_file->name = filename;
	new_file->next = filelist->next;
	new_file->prev = filelist;
	filelist->next = new_file;
}

/*
**
*/
int create_list(const char *fpath, const struct stat *sb, int flag);
int create_list(const char *fpath, const struct stat *sb, int flag)
{
	if (flag == FTW_F)
	{
		write_in_filelist(fpath, List1);
		List1 = List1->next;
	}
	return 0;
}

int main(void)
{
	List1 = (struct chain*)malloc(sizeof(struct chain));
	List1->name = "dir2";
	List1->next = List1->prev = 0;
	ftw("dir2", create_list, 20);
	for (; List1 != 0; List1 = List1->prev)
		printf("%s\n", List1->name);
	return 0;
}
