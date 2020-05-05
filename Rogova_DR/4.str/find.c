#include"stdio.h"
#include"stdlib.h"
#include"string.h"

char *read_string(FILE *);
int len(char * str);
int * find(char * small, char * big);

char *read_string(FILE * input)
{
	int i = 0;
	char el;
	char buf[1];
	char *s = (char *) malloc(1 * sizeof(char));
	s = fgets(s, 1, input);
	buf[0] = s[0];
	while(s[i] != '\n')
	{
		i++;
		s = (char *)  realloc(s, i * sizeof(char));
		buf = (char *) realloc(s, i * sizeof(char));
		if(fscanf(input, "%c", &el) == 1)
			s[i] = el;
		else 
			return NULL;
		buf[i] = str[i];
	}

	return buf;
}



