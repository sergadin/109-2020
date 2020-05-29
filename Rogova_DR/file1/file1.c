#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




static const char *s;
static const char *sym;




static int proverka(const char *s, const struct stat *sb, int flag)
{
    if (flag == FTW_F) 
    {
        char *str = NULL;
	size_t lenn = 0;
	int ind = 0;
	FILE * f;
	if((f = fopen(s, "r")) != NULL)
	{
		while((getline(&str, &lenn, f)) != -1)
		{
			if(strstr(str, sym) != NULL)
			{
				ind = 1;
			}
			if(ind == 1)
				break;	
		}
		if(str)
			free(str);
		if(ind == 1)
		{
			printf("%s\n", s);
		}
		ind = 0;
		fclose(f);
	 }
    }
    return 0;         
}

int main(int argc, char *argv[]) 
{
    if(argc == 2) 
    {
       s = argv[1];
       sym = " ";
       ftw(s, proverka, 36);
    }
    else
    {
	    printf("eshe_raz\n");
    }
    return 0;
}
