#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include"findstr.h"
char *readstring(FILE * input);
char *readstring(FILE * input)
{
	int l, p = 0;
	char *res;
	char buf[1024];
	char *s;
	s = fgets(buf, 1024, input);
	if(s)
	{
		l = strlen(s);
		res = (char *) malloc((l + 1)*sizeof(char));
		strcpy(res, s);
		while((s) && (s[strlen(s) - 1] != '\n'))
		{
			strcpy(res, s);
			s = fgets(buf, 1024, input);
			if(s)
			{
				p = strlen(s);
				l += p;
		        	res = (char *) realloc(res, l);
			}
		
		}
		return res;
	}
	return NULL;
}
	
void findstr(char * smallstr, FILE * input)
{
	char * bigstr;
	int i = 0;
	int ind = 0;
	bigstr = readstring(input);
	while(bigstr != NULL)
	{
		i++;
		printf("%s\n%s\n", smallstr, bigstr);
		if(strstr(bigstr, smallstr) != NULL)
		{
			ind = (int)(strstr(bigstr, smallstr) - bigstr);
			printf("str:_%d;_pos:_%d\n", i, ind);
		}
		bigstr = readstring(input);
	}




}

