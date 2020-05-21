#include"stdio.h"
#include"stdlib.h"
#include"findstr.h"
int len(char *s);
char *readstring(FILE *input);
char *strcpy(char *t, char *s);
void zamena(char * str, char *s, char *forwhat, FILE *output);
int findstr(char * t, char *w);
int posstr(char * str, char *s);
void pstr(FILE * output, char * str);
void str_of_def(char * allstr, char * what, char * forwhat, char * def);


int findstr(char * t, char *w) 
{
		int i, j = 0;
		int p = 0, le = 0;
       		int n1 = 0;	
		le = len(t);
		n1 = len(w);
		if(le < n1)
			return 0;
		for(i = 0; i < le - n1; i++) 
		{
			p = 0;
			j = 0;
			while((t[i + j] == w[j]) && (j < n1))
			{
				j++;	
				p = p + 1;
			}
			if(p == n1)
			{
				return 1;
			}
				
				
		}
			
		
	
	
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
	def = readstring(f_with_def);
	printf("%s", def);
	undef = readstring(f_with_def);
	printf("%s", undef);
	do{
		strnow = readstring(input);
		printf("%s", strnow);
		if((findstr(strnow, def) == 0) && (findstr(strnow, undef) == 0))
				pstr(output, strnow);
		if(findstr(strnow, def) != 0)
		{       
			printf("%s", strnow);
			str_of_def(strnow, what, forwhat, def);
			free(strnow);
			strnow = readstring(input);
			while((strnow != NULL) && (findstr(strnow, undef) == 0))
			{
				zamena(strnow, what, forwhat, output);
				free(strnow);
                       	        strnow = readstring(input);
           		}
			if(strnow)
			{
				free(strnow);
				strnow = readstring(input);
				while(strnow && (findstr(strnow, def) == 0))
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
void zamena(char * str, char *s, char *forwhat, FILE *output)
{
	int j = 0;
	int p = 0;
        int l_1 = len(str);
        int l_2 = len(s);
        int l_3 = len(forwhat);
	while(findstr(str, s) != 0)
	{
		p = posstr(str, s);
		for(j = 0; j < p; j ++)
		{
			fprintf(output, "%c", str[j]);
		}
		for(j = 0; j < l_3; j ++)
		{
			fprintf(output, "%c", forwhat[j]);
		}
		for(j = p + l_2; j < l_1; j ++)
		{
			fprintf(output, "%c", str[j]);
		}

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


