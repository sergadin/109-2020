#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ftw.h>
#include <sys/stat.h>


char **d1; // имена файлов из dir1
char **d2; // имена файлов из dir2
int file_counter1 = 0; // количество файлов dir1
int file_counter2 = 0; // количество файлов dir2

int files_dir1(const char *path, const struct stat *st, int flag)
{
    if (flag == FTW_F)
    {
        char *temp;
        if (strrchr(path, '/') != NULL)
        {
            file_counter1++;
            temp = strrchr(path, '/');
            
            d1 = realloc(d1, sizeof(char*) * (file_counter1+ 1));
            d1[file_counter1] = malloc(sizeof(char) * (strlen(temp) + 1));
            
            strcpy(d1[file_counter1], temp);
        }
    }
    
    return 0;
}

int files_dir2(const char *path, const struct stat *st, int flag)
{
    if (flag == FTW_F)
    {
        char *temp;
        
        if (strrchr(path, '/') != NULL)
        {
            file_counter2++;
            temp = strrchr(path, '/');
            
            d2 = realloc(d1, sizeof(char*) * (file_counter1+ 1));
            d2[file_counter2] = malloc(sizeof(char) * (strlen(temp) + 1));
            
            strcpy(d2[file_counter2], temp);
        }
    }
    
    return 0;
}



void raznost(char **d1,char **d2,int filecount1,int filecount2)
{
  //  char *filename;
  //  int max;
    
  //  if (filecount1>filecount2)
  //  {
    //   d2 = realloc(d1, sizeof(char*) * (file_counter1));
    //    for (int i = file_counter2; i < file_counter2;i++)
        
  //  }
   
    
    printf("Разность DIR1 и DIR2\n");
    for(int i=0; i < filecount1; i++)
        for(int j=0; j < filecount2; j++)
            if(strcmp(d1[i],d2[j])==0)
            {
                printf("%s\n",d1[i]);
                
            }
    
    
    printf("Разность DIR2 и DIR1\n");
    for(int j=0; j < filecount1; j++)
        for(int i=0; i < filecount2; i++)
            if(strcmp(d1[i],d2[j])==0) printf("%s\n",d2[i]);
}


int main(int argc, char **argv)
//int main(void)
{
  if( (argc != 3) )
    {
        printf("формат ввода: Имя первой дериктории - Имя второй дериктории ");
       return -1;
}
   
        ftw(argv[1], files_dir1, 10);
        ftw(argv[2], files_dir2, 10);
   // ftw("dir1", files_dir1, 10);
    // ftw("dir2", files_dir2, 10);
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
