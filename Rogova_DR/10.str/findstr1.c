#include"stdio.h"
#include"stdlib.h"
#include"findstr.h"
#include"string.h"


int len(const char *s);
int posstr(char * t, char *w);
char *readstring(FILE *input);
char *strcpy(char *t, const char *s);
int findstr(char * t, const char *w);
int dlina(char *t, int k);
char* zamena(char * t, char * what, char * forwhat);
char * makewhat(char *strnow, const char* def);
char * makeforwhat(char *strnow, const char* def);
void deleteel(int i, char ** mas, int num);
int poisk(char * t, char * w);
int pospoisk(char * t, char * w);
char * makeundef(char * str);






int len(const char *s)
{
        int n = 0;
        while (*s++)
        {
                n++;
        }
        return n;
}

char *strcpy(char *t, const char *s)
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

int findstr(char * t, const  char *w) 
{
	if(len(w) > len(t))
		return 0;
	int i, j = 0;
	int p = 0, le = 0;
	int n1 = 0;
	le = len(t);
	n1 = len(w);
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
	return 0;	
}

int posstr(char * t, char *w)
{
        int i, j = 0;
        int p = 0;
        int n1 = 0;
        int le = len(t);
        n1 = len(w);
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
                        return i;
                }

        }
}


                      
void mainstrd(FILE * input, FILE * output, FILE * deffile)
{
	char * def;
	char * undef;
	char *what;
	char *forwhat;
	char *strnow;
	char * news;
	char ** maswhat = NULL;
	char ** masforwhat = NULL;
	int lenmas = 0;
	int num = 0;
	int ind = 0;
	def = malloc(8);
	undef = malloc(7);
	def = strcpy(def, "#define");
	undef = strcpy(undef, "#undef");
	def[7] = '\0';
	undef[6] = '\0';
	int indec = 0;
	char* whatu;
	while((strnow = readstring(input)) != NULL)
	{
		if(findstr(strnow, def) != 0)
		{
			what = makewhat(strnow, def);
			printf("what:%s\n", what);
			printf("%s\n_____stroka", what);
			forwhat = makeforwhat(strnow, def);
			printf("%s\n____forwhat", forwhat);
			for(int i = 0; i < num; i++)
			{
				if((poisk(maswhat[i], what) != 0) && (len(maswhat[i]) == len(what)))
				{
					free(masforwhat[i]);
					masforwhat[i] = malloc(len(forwhat) + 1);
					for(int j = 0; j <= len(forwhat); j++)
					{
						masforwhat[i][j] = forwhat[j];

					}
					ind = 1;

				}
			}
		
			if(ind == 0)
			{
				maswhat = realloc(maswhat, (num + 1)* sizeof(char *));
				masforwhat = realloc(masforwhat, (num + 1) * sizeof(char *));
				num ++;
				maswhat[num - 1] = NULL;
				masforwhat[num - 1] = NULL;
				maswhat[num - 1] = realloc(maswhat[num - 1], len(what) + 1);
				masforwhat[num - 1] = realloc(masforwhat[num - 1], len(forwhat) + 1);
				for(int i = 0; i <= len(what); i++)
				{
					maswhat[num - 1][i] = what[i];
				}
				for(int i = 0; i <= len(forwhat); i++)
				{
					masforwhat[num - 1][i] = forwhat[i];

				}
			}
			ind = 0;
		free(what);
		free(forwhat);
		}
		ind = 0;
		if(findstr(strnow, undef) != 0)
		{
			whatu = makeundef(strnow);
			for(int j = 0; j < num; j++)
			{
				if((poisk(maswhat[j], whatu) != 0) && (len(maswhat[j]) == len(whatu)))
				{
					deleteel(j, maswhat, num); 
					deleteel(j, masforwhat, num);
					num -= 1;
				}
			}
		}
		if((findstr(strnow, def) == 0) && (findstr(strnow, undef) == 0))
		{
			printf("%d\nNUMMM:", num);
			for(int i = 0; i < num; i ++)
			{
				printf("%d_%s_%s__%s\n", poisk(strnow, maswhat[i]), strnow, maswhat[i], masforwhat[i]);
				if(poisk(strnow, maswhat[i]) != 0)
				{
					strnow = zamena(strnow, maswhat[i], masforwhat[i]);
					printf("%s\n!!!!!!!!!!!", strnow);
					indec = 1;
				}
			}
			if(indec == 1)
			{
				fprintf(output, "%s\n", strnow);
			}            
			if(indec == 0)
			{
				fprintf(output, "%s\n", strnow);
			}
			indec = 0;



		}
		
	}	
free(strnow);	
free(def);
free(undef);
for(int i = 0; i < num; i ++)
{
	free(maswhat[i]);
	free(masforwhat[i]);
}
free(maswhat);
free(masforwhat);
}
char* zamena(char * str, char * what, char * forwhat)
{
	char * newstr;
	char * strnow = malloc(len(str) + 1);
	strnow = strcpy(strnow, str);
	int lenn = 1;
	int pos;
	int j;
	while(poisk(strnow, what) != 0)
	{
		newstr = malloc(1);
		lenn = 1;
		pos = pospoisk(strnow, what);
		for(int i = 0; i < pos; i++)
		{
			newstr = realloc(newstr, lenn);
			lenn ++;
			newstr[i] = strnow[i];
		}
		for(int i = 0; i < len(forwhat); i ++)
		{
			newstr = realloc(newstr, lenn);
			lenn ++;
			newstr[pos + i] = forwhat[i];
			j = pos + i + 1;
		}
		
		for(int i = pos + len(what); i <= len(strnow); i ++)
		{
			newstr = realloc(newstr, lenn + 1);
			lenn ++;
		       	newstr[len(forwhat) - len(what) + i] = strnow[i];
		}
		newstr[lenn - 1] = '\0';
		strnow = realloc(strnow, len(newstr) + 1);
		strcpy(strnow, newstr);
		free(newstr);	
	}
	return(strnow);
}


char *  makewhat(char *strnow,  const char* def)
{
	char* what;
	int d = len(strnow);
	int d1 = 1;
	int i = 8, j = 0;
	what = malloc(1);
	while(strnow[i] != ' ')
	{	
		d1 += 1;
		what = realloc(what, d1);
		what[j] = strnow[i];
		printf("%c\n", what[j]);
		i++;
		j++;
	}
	what[d1 - 1] = '\0';
	i++;
	printf("%s\nWHAT", what);
	printf("%d\n", len(what));
	return what;

}
char *  makeforwhat(char *strnow,  const char* def)
{
	char * forwhat;
        int d = len(strnow);
        int d1 = 1, d2  = 1;
        int i = 0, j = 0;
	forwhat = malloc(1);
        while(strnow[i] != ' ')
        {
                i++;
        }
        i++;
        while(strnow[i] != ' ')
        {
                d1 += 1;
                i++;
                j++;
        }
        i++;
        j = 0;
	while(strnow[i] != '\n')
        {
		d2 += 1;
                forwhat = realloc(forwhat, d2);
                forwhat[j] = strnow[i];
                i++;
                j++;
        }
	forwhat[d2 - 1] = '\0';
	return forwhat;
}

void deleteel(int i, char ** mas, int num)
{
	for(int j = i; j < num - 1; j++)
	{
	 	free(mas[j]);
		mas[j] = malloc(len(mas[j + 1]) + 1);
		for(int k = 0; k <= len(mas[j + 1]); k++)
		{
			mas[j][k] = mas[j + 1][k];
		}

	}
}
int poisk(char * t, char * w)
{
	if(len(t) < len(w))
		return 0;
	int i, j = 0;
        int p = 0, le = 0;
        int n1 = 0;
        le = len(t);
        n1 = len(w);
        for(i = 0; i <= le - n1; i++)
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
			if((i == 0) || (t[i - 1] == ' '))
			{
				if(((i + len(w)) == len(t)) || (t[i + len(w)] == ' ') || (t[i + len(w) + 1] == '\0'))
				{
					return 1;
				}
			}
                }

        }
        return 0;
}
char * makeundef(char * str)
{
	char * w = NULL;
	int le = 1;
	for(int i = 7; i < len(str) - 1; i++)
	{
		w = realloc(w, le);
		w[i - 7] = str[i];
		le ++;
	}
	w[le - 1] = '\0';
	return w;

}
int pospoisk(char * t, char * w)
{
        int i, j = 0;
        int p = 0, le = 0;
        int n1 = 0;
        le = len(t);
        n1 = len(w);
        for(i = 0; i <= le - n1; i++)
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
                        if((i == 0) || (t[i - 1] == ' '))
                        {
                                if((t[i + len(w)] == ' ') || (t[i + len(w) + 1] == '\0'))
                                {
                                        return i;
                                }                          
                        }
                }

        }
        return 0;


}


