/**
 ** Для двух заданных каталогов напечатать два списка фай- лов: присутствующих в одном каталоге и отсутствующих в другом.
 **
 ** Параметры:
 **  int argc (argument count) - кол-во аргументов
 **  char *argv[] - имена катаологов
 **
 **
 ** Метод:
 **  ftw() перемещается по дереву каталогов, начиная с указанного каталога dir.Имя каждого элемента дерева 1 и дерева 2 записываются в массив dir1 и dir2.Затем сравниеваем массивы поэлементно через strcmp
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ftw.h>
#include <sys/stat.h>
#include <dirent.h>

char **d1; // имена файлов из dir1
char **d2; // имена файлов из dir2
//unsigned long *file_counter []   = {0 ,0}; // количество файлов
int file_counter1,file_counter2;

void listdir1(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;
    
    if (!(dir = opendir(name)))
        return;
    
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
          //  snprintf(path, sizeof(path),"%s/%s", name, entry->d_name);
            
            d1 = realloc(d1, sizeof(char*) * (file_counter1+ 1));
            d1[file_counter1] = malloc(sizeof(char) * (strlen(entry->d_name) + 1));
            //printf("%*s[%s]\n", indent, "", entry->d_name);
            listdir1(path, indent + 2);
        } else {
           // printf("2 %*s- %s\n", indent, "", entry->d_name);
            d1 = realloc(d1, sizeof(char*) * (file_counter1+ 1));
            d1[file_counter1] = malloc(sizeof(char) * (strlen(entry->d_name) + 1));
        }
        file_counter1++;
    }
    closedir(dir);
}

void listdir2(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;
    
    if (!(dir = opendir(name)))
        return;
    
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            //  snprintf(path, sizeof(path),"%s/%s", name, entry->d_name);
            
            d2 = realloc(d2, sizeof(char*) * (file_counter2+ 1));
            d2[file_counter2] = malloc(sizeof(char) * (strlen(entry->d_name) + 1));
            //printf("%*s[%s]\n", indent, "", entry->d_name);
            listdir2(path, indent + 2);
        } else {
            // printf("2 %*s- %s\n", indent, "", entry->d_name);
            d2 = realloc(d2, sizeof(char*) * (file_counter2+ 1));
            d2[file_counter2] = malloc(sizeof(char) * (strlen(entry->d_name) + 1));
        }
        file_counter2++;
    }
    closedir(dir);
}



void raznost(char **d1,char **d2,int filecount1,int filecount2)
{
   
    
    printf("Разность DIR1 и DIR2\n");
    for(int i=0; i < filecount1; i++)
       for(int j=0; j < filecount2; j++)
            if(strcmp(d1[i],d2[j])==0)

              printf("%s\n",d1[i]);
                
        
    
    
    printf("Разность DIR2 и DIR1\n");
    for(int j=0; j < filecount2; j++)
        for(int i=0; i < filecount1; i++)
            if(strcmp(d1[i],d2[j])==0)
                printf("%s\n",d2[i]);
}


//int main(int argc, char **argv)
int main(void)
{
   // if( (argc != 3) )
   // {
   //     printf("формат ввода: Имя первой дериктории - Имя второй дериктории ");
   ///     return -1;
   // }
    
    //ftw(argv[1], files_dir1, 10);
    //ftw(argv[2], files_dir2, 10);
     //ftw("dir1", files_dir1, 10);
    // ftw("dir2", files_dir2, 10);
 
     listdir1("dir1", 0);
   
     listdir2("dir2", 0);
    raznost(d1,d2,file_counter1,file_counter2);
    for (int i = 0; i < file_counter1; i++)
    {
        free(d1[i]);
    }
    free(d1);
    
    for (int i = 0; i < file_counter2; i++)
    {
        free(d2[i]);
    }
    free(d2);
    
    return 0;
}
