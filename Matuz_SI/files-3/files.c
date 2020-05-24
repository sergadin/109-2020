#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ftw.h>
#include <sys/stat.h>


char *data;
int len = 1;

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
		     printf("11%s \n", filename); 
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
        printf("%s \n", data); 
        ftw(argv[2], compare_filenames, 10);
    }
    else
	printf("smth wrong");
    free(data);
    return 0;
}
