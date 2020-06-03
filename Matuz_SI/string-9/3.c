#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* incl = "#include ";

int len(const char *s)
{
    int n = 0;
    while (*s++)
	n++;
    return n;
}

char *strcpy(char *t, const char *s)
{
    int n;
    n = len(s);
    for (int i = 0; i < n + 1; i++)
        t[i] = s[i];
    return t;
}       
                        
char *readstring(FILE * input)
{
    int l, p = 0;
    char *res;
    char buf[1024];
    char *s;
    s = fgets(buf, 1024, input);
    if(s)
    {
	l = len(s);
	res = (char *) malloc((l + 1)*sizeof(char));
	strcpy(res, s);
	while((s) && (s[len(s) - 1] != '\n'))
        {
	    strcpy(res, s);
	    s = fgets(buf, 1024, input);
            if(s)
            {
		p = len(s);
		l += p;
	       	res = (char *) realloc(res, l);
	    }
	}
	return res;
    }
    return NULL;
}


void include(FILE *output, char *filename, char *filelist)
{
    //char *check = strstr(filelist, filename);
    char *nextfilename;
    FILE *file;
//for reading
    char *data = NULL;


    int len = 0;
    int old_len = 0;

    //check whether filename is in filelist
    //???
printf("1\n");
    if ((file = fopen(filename, "r")) == NULL)
    {
        printf("cannot open file %s \n",filename);
        return;
    }
    //write filename in filelist
    old_len = strlen(filelist);
    len = strlen(filelist) + strlen(filename);
    filelist = realloc(filelist, len+2);
    strncpy(filelist + old_len, filename, strlen(filename));
    filelist[len] = ' ';
    filelist[len + 1] = '\0';

printf("%s \n", filelist);
    //read file
    while((data = readstring(file)) != NULL)
    {

	if (strncmp(data, incl, 9) == 0)
	{
	    nextfilename = malloc((strlen(data) - 9)*sizeof(char)); 
	    strncpy(nextfilename, data + 9, (strlen(data) - 9 -1));
	    nextfilename[strlen(data) - 9 - 1] = '\0';
printf("%s \n", nextfilename);
    


	    include(output, nextfilename, filelist);
	    free(nextfilename);
	}
	else
	{
	    fprintf(output, "%s", data);
	}
	free(data);

    }
    
    fclose(file);
//delete filename in filelist
   /* filelist = realloc(filelist, old_len);
    filelist[old_len-1] = '\0';
    printf("%s \n", filelist);*/
    return;
}



int main(void)
{
    char *filelist = malloc(2 * sizeof(char));
    filelist[0] = ' ';
    filelist[1] = '\0';
    
    char *filename = "input.txt";
    FILE *output;
    if ((output = fopen("result.txt", "w")) == NULL)
    {
        printf("cannot open output file \n");
        return -1;
    }
    include(output, filename, filelist);

//cleaning
    fclose(output);
  // here problem
 //free(filelist);

    return 0;
}
