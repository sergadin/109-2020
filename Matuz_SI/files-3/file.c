#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ftw.h>
#include <sys/stat.h>


char *data;
//char *filename;
int len = 1;

static int get_filenames(const char *fpath, const struct stat *status, int tflag)
{
    if (tflag == FTW_F)
    {
printf("3\n");
        char *temp;
        if (strrchr(fpath, '/') != NULL)
        {
            temp = strrchr(fpath, '/');
	    //printf("%ld\n", strlen(temp));
            data = realloc(data, len + strlen(temp)+1);
            //printf("%ld\n", len + strlen(temp) + 1); 
printf("2\n");
	    strcpy(data + len, temp); 
            data[len + strlen(temp)] = ' ';
            len += (strlen(temp)+1);          
        }
printf("1\n");
        
    }
    return 0;
}



/*static int compare_filenames(const char *fpath, const struct stat *status, int tflag)
{
    if (tflag == FTW_F)
    {
        char *temp;
        if (temp = strrchr(fpath, '/'))
        {
	    
	    printf("%s\n", temp);
            filename = realloc(filename, strlen(temp) - strlen(strchr(temp, '.')));
            
            strcpy(filename, temp);
            printf("22 %s \n", filename); 
            filename[strlen(temp) - strlen(strchr(temp, '.'))] = ' ';

            if (strstr(data, filename))
		printf("11 %s \n", filename);
                
        }
        free(temp);
    }
    return 0;
}*/


int main(int argc, char *argv[])
{
    data = malloc(2 * sizeof(char));
    //filename = malloc(2 * sizeof(char));
    //filename[0] = ' ';
    data[0] = ' ';
    /*if (argc == 1)
    { 
	ftw(".", get_filenames, 1);
        printf("%s \n", data); 
    }*/
    if (argc == 3)
    {
	ftw(argv[1], get_filenames, 10);
        printf("%s \n", data); 
        //ftw(argv[2], compare_filenames, 10);
    }
    //free(filename);
    free(data);
    return 0;
}
