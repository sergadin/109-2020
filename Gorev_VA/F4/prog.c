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
	while ((i >= 0) && (filename[i] != '/'))
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
	while (last_file->next != 0)
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
	while (FL != 0)
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