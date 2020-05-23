/** (это всё, как я хотела бы, чтобы это всё работало)
 ** Задача:
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




//#include <stdio.h>
/*i thought to use files instead of global array*/

#include <stdlib.h>

#include <string.h>

#include <ftw.h>
#include <sys/stat.h>

//#define N 1024
//#define NAME_MAX 255


/*i found this in one smart book*/
int list(const char *name, const struct stat *status, int type)
{
    if(type == FTW_NS)
        return 0;

    if(type == FTW_F)
        printf("0%3o\t%s \n", status->st_mode&0777, name);

    return 0;
}

/** Функция get_filenames
 **
 ** Цель:
 **     получить именя файлов из path
 **
 **
 ** Как делает:
 **     strrchr находит последнее включение '/', получая "/название файла"
 **
 **     потом какими-то шаманскими операциями было бы неплохо сохранить куда-то
 **
 **
 **/

static int get_filenames(const char *fpath, const struct stat *status, int tflag)
{
    if (tflag == FTW_F)
    {
        char *temp;
        if (temp = strrchr(fpath, '/'))
        {
            printf("%s \n", temp);
        }
        
    }
    return 0;
}



int main(int argc, char *argv[])
{
    if (argc == 1)
	ftw(".", get_filenames, 1);
    return 0;
}


/* Для меня про ftw()
 *
 * int fn(const char *fpath, const struct stat sb, int typeflag)
 * int ftw(const char *dirpath, int (*fn),int nopenfd);
 *
 * The argument nopenfd should be in the range [1, {OPEN_MAX}]
 * The nopenfd argument shall specify the maximum number of directory streams or
 * file descriptors or both available for use by ftw() while traversing the tree.
 * When ftw() returns it shall close any directory streams and file descriptors
 * it uses not counting any opened by the application-supplied fn function.
 *
 * If the function pointed to by fn returns a nonzero value,
 * ftw() stops its tree traversal and returns whatever value
 * was returned by the function pointed to by fn().
 *
 * FTW_F    The object is a  file
 * FTW_D    ,,    ,,   ,, ,, directory
 * FTW_DNR  ,,    ,,   ,, ,, directory that could not be read
 * FTW_SL   ,,    ,,   ,, ,, symbolic link
 * FTW_NS   The object is NOT a symbolic link and is one for
 *          which stat() could not be executed
 *
 * */