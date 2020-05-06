#include"stdio.h"
#include"stdlib.h"
#include"findstr.h"
int len(char *s);
char *readstring(FILE *input);
char *strcpy(char *t, char *s);
void zamena(char * str, char *s, char *forwhat);
int findstr(char * t, char *w);
int posstr(char * str, char *s);
void pstr(FILE * output, char * str);
void str_of_def(char * allstr, char * what, char * forwhat, char * def);


int findstr(char * t, char *w) 
{
	int i, j;
	int result = 0;
	int p = 0, l = 0;
        int n1 = 0;	
	l = len(t);
	n1 = len(w);
	for(i = 0; i < l - n1; i++) 
	{
		if(t[i] == w[0])
		{
			for(j = 0; j < n1; j++)
			{
				if(t[i + j] == w[j])
				{
					p = p + 1;
				}
			}
		}
		if(p == n1)
		{
			result ++;
		}
		p = 0;
	
	}
	return result;
		
}
int len(char *s) 
{
	int n = 0;
	while (*s++) 
	{
		n++;
	}	
	return n;
}

char *strcpy(char *t, char *s) 
{
	int n; 
	n = len(s);
	for (int i = 0; i < n + 1; i++) 
	{
		t[i] = s[i];
	}
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

void ch_fl_wth_def(FILE * input, FILE * output, FILE * f_with_def)
{
	char * strnow;
	char * what;
	char * forwhat;
	char * def;
	char * undef;
	int l, lw, lf;
	def = "define#";
	undef = "undef#";
	do{
		strnow = readstring(input);
		if((findstr(strnow, def) == 0) && (findstr(strnow, undef) == 0))
				pstr(output, strnow);
		if(findstr(strnow, def) != 0)
		{
			str_of_def(strnow, what, forwhat, def);
			free(strnow);
			strnow = readstring(input);
			while((findstr(strnow, undef) == 0) && (strnow != NULL))
			{
				printf("prev in main");
				zamena(strnow, what, forwhat);
				pstr(output, strnow);
				free(strnow);
                       	        strnow = readstring(input);
           		}
			if(findstr(strnow, undef) != 0)
			{
				free(strnow);
				strnow = readstring(input);
				while((findstr(strnow, def) == 0) && (strnow != NULL))
				{
					printf("last in main");
					pstr(output, strnow);
					free(strnow);
				        strnow = readstring(input);	
				}
			}
		}
		free(strnow);

	}while(strnow != NULL);
}
void zamena(char * str, char *s, char *forwhat)
{
	int i, j;
        int l_1 = len(str);
        int l_2 = len(s);
        int l_3 = len(forwhat);
        char * newstr;
	while(findstr(str, s) != 0)
	{
		printf("za");
		l_1 = len(str);
		l_2 = len(s) - 1;
		l_3 = len(forwhat) - 1;
		newstr = malloc(l_1 + (l_3 - l_2));
		i = posstr(str, s);
		for(j = 0; j < i; j ++)
		{
			newstr[j] = str[j];
		}
		for(j = i; j < i + l_3; j++)
		{
			newstr[j] = forwhat[j - i];
		}
		for(j = i + l_3; j <= len(newstr); j ++)
		{
			newstr[j] = str[j - l_3 + l_2];
		}
		str = realloc(str, len(newstr));
		strcpy(str, newstr);
		free(newstr);	

	}
	
}
int posstr(char * str, char *s)
{
	int p = 0;
	int l1 = len(str), l2 = len(s);
	for(int i = 0; i < l1 - l2; i++)
	{
		if(str[i] == s[0])
		{
			for(int j = 0; j < l2; j++)
			{
				if(str[i + j] = s[j])
					p ++;
			}	
		}
		if(p == l2)
		{
			return i;
		}
		p = 0;
	}

}

void pstr(FILE * output, char * str)
{
	fprintf(output,"%s\n", str);
}


void str_of_def(char * allstr, char * what, char * forwhat, char * def)
{
	int l = len(allstr);
	int i = 0;
	while(allstr[i] == def[i])
		i++;
	i += 2;
	while(allstr[i] != ' ')
	{
		i++;
	}
	what = malloc(i - 7 + 1);
	forwhat = malloc(l - i - 1);
	for(int j = 8; j <= i; j++)
	{
		what[j - 8] = allstr[j];
	}
	what[i + 1] = '\0';
	i += 2;
	for(int j = i; j <= l; j++)
	{
		forwhat[j-i] = allstr[j];
	}

}


