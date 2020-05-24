struct chain // реализация списка файлов
{
	char *name;         // имя файла 
	struct chain *next; // указатель на следующий файл в списке
	                    // если следующего нет, то 0
	struct chain *prev; // указатель на предыдущий файл в списке
	                    // если предыдущего нет, то 0
};

char *file_name(const char *filename);
int write_in_filelist(const char *filename, struct chain *filelist);
int find_file_in_list(char *short_filename, struct chain *filelist);
int func_for_ftw(const char *fpath, const struct stat *sb, int flag);
int dif();
