/** Задача:
 **
 **     Для двух заданных каталогов напечатать список файлов,
 **     имеющих совпадающие имена
 **
 ** Параметры:
 **     int argc (argument count) - кол-во аргументов
 **     char *argv[] (argument value) - значения аргументов,
 **                             переданных при запуске (массив аргументов)
 ** Входные данные:
 **     2 аргумента: две заданные директории
 **     остальное мы с программой не признаём
 **
 ** Результат программы:
 **     будет напечатан список файлов с совпадаюшими именами
 **
 **
 ** Метод:
 **     использование функции ftw() из ftw.h
 **     (рекурсивно спускается по иерархии каталогов,
 **     находящихся в path)
 **
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ftw.h>
#include <sys/stat.h>


char *data;
int len = 1;

/** Функция get_filenames
 **
 ** Цель:
 **     получить имена файлов из path
 **
 ** Как делает:
 **     strrchr находит последнее включение '/', получая "/название файла.расширение файла"
 **     strstr находит первое включение '.', получая ".расширение файла"
 **     записываем " /имя файла"
 **/
static int get_filenames(const char *fpath, const struct stat *status, int tflag)
{
    if (tflag == FTW_F)
    {
//printf("3\n");
        char *temp;
        if (strrchr(fpath, '/') != NULL)
        {
            temp = strrchr(fpath, '/');
	    //printf("%ld\n", strlen(temp));
            data = realloc(data, len + strlen(temp)+1);
            //printf("%ld\n", len + strlen(temp) + 1); 
//printf("2\n");
	    strcpy(data + len, temp); 
            data[len + strlen(temp)] = ' ';
            len += (strlen(temp)+1);          
        }
//printf("1\n");
        
    }
    return 0;
}


/** Функция get_filenames
 **
 ** Цель:
 **     сравнить имена файлов из path директории с data
 **
 ** Как делает:
 **     strrchr находит последнее включение '/', получая "/название файла.расширение файла"
 **     strstr находит первое включение '.', получая ".расширение файла"
 **     записываем " /имя файла"
 **
 **     понимает strstr'ом, входит ли имя данного файла в data
 **/

static int compare_filenames(const char *fpath, const struct stat *status, int tflag)
{
    if (tflag == FTW_F)
    {   
        char *temp;
        char *filename;
        filename = malloc(2 * sizeof(char));
        filename[0] = ' ';
        if (temp = strrchr(fpath, '/'))
        { 
	    //printf("00%s\n", temp);
	    if (strchr(temp, '.') != NULL)
	    {
		//printf("01%s \n", strchr(temp, '.'));
		filename = realloc(filename, strlen(temp) - strlen(strchr(temp, '.'))+2+1);
            // 1 - space in the beginning, 1 - space in the end, 1 - /0
                for (int k = 1; k < (strlen(temp) - strlen(strchr(temp, '.'))+1); k++)
		     filename[k] = temp[k-1];
                //filename[strlen(temp) - strlen(strchr(temp, '.')) + 1] = ' ';
		filename[strlen(temp) - strlen(strchr(temp, '.')) + 1] = '\0';
                if (strstr(data, filename))
		     printf("%s \n", filename);
             }
        }
        free(filename);
    }
    return 0;
}


int main(int argc, char *argv[])
{
    data = malloc(2 * sizeof(char));
    data[0] = ' ';
    if (argc == 3)
    {
	ftw(argv[1], get_filenames, 10);
        data = realloc(data, len+1);
        data[len] = '\0';
        //printf("%s \n", data);
        ftw(argv[2], compare_filenames, 10);
    }
    else
	printf("try to use this marvelous prog with args containing dir1 and dir2 \n");
    free(data);
    return 0;
}
