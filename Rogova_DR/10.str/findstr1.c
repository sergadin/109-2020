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
	char ** maswhat = NULL;
	char ** masforwhat = NULL;
	int lenmas = 0;
	int num = 0;
	int ind = 0;
	def = malloc(8);
	undef = malloc(7);
	printf("%d\n", len(undef));
	printf("%s\n", undef);
	def = strcpy(def, "#define");
	undef = strcpy(undef, "#undef");
	while((strnow = readstring(input)) != NULL)
	{
		if(findstr(strnow, def) != 0)
		{
			printf("%s_s_\n", strnow);
			what = makewhat(strnow, def);
			printf("%c\n", what[len(what) - 1]);
			forwhat = makeforwhat(strnow, def);
			for(int i = 0; i < num; i++)
			{
				printf("%d\n_i", i);
				if((findstr(maswhat[i], what) != 0) && (len(maswhat[i]) == len(what)))
				{
					free(masforwhat[i]);
					masforwhat[i] = malloc(len(forwhat));
					for(int j = 0; j <= len(forwhat); j++)
					{
						masforwhat[i][j] = forwhat[j];

					}

				}
				ind = 1;
			}
		
			if(ind == 0)
			{
				maswhat = realloc(maswhat, (num + 1)* sizeof(char *));
				masforwhat = realloc(masforwhat, (num + 1) * sizeof(char *));
				num += 1;
				maswhat[num] = realloc(maswhat[num], len(what));
				masforwhat[num] = realloc(masforwhat[num], len(forwhat));
				for(int i = 0; i <= len(what); i++)
				{
					maswhat[num][i] = what[i];
				}
				for(int i = 0; i <= len(forwhat); i++)
				{
					masforwhat[num][i] = forwhat[i];

				}
				free(what);
				free(forwhat);
			}
			ind = 0;
		}
		if(findstr(strnow, undef) != 0)
		{
			what = makeundef(strnow);
			for(int j = 0; j < num; j++)
			{
				if((findstr(maswhat[j], what) != 0) && (len(maswhat[j]) == len(what)))
				{
					deleteel(j, maswhat, num); 
					deleteel(j, masforwhat, num);
					num -= 1;
				}
			}
		}
		if((findstr(strnow, def) == 0) && (findstr(strnow, undef) == 0))
		{
			for(int i = 0; i < num; i ++)
			{
				if(poisk(strnow, maswhat[i]) != 0)
				{
					printf("jjjjjjjjjjjj\n");
					zamena(strnow, maswhat[i], masforwhat[i]);
					fprintf(output, "%s\n", strnow);
				}
			}
		}
	
	}						

}
char* zamena(char * strnow, char * what, char * forwhat)
{
	char * newstr = malloc(1);
	int pos;
	int j;
	while(poisk(strnow, what) != 0)
	{
		pos = pospoisk(strnow, what);
		for(int i = 0; i < pos; i++)
		{
			newstr = realloc(newstr, len(newstr) + 1);
			newstr[i] = strnow[i];
		}
		for(int i = 0; i < len(forwhat); i ++)
		{
			newstr = realloc(newstr, len(newstr) + 1);
			newstr[pos + i] = forwhat[i];
			j = pos + i + 1;
		}
		
		for(int i = pos + len(what); i <= len(strnow); i ++)
		{
			newstr = realloc(newstr, len(newstr) + 1);
		       	newstr[len(forwhat) - len(what) + i] = strnow[i];
		}
		strnow = realloc(strnow, len(newstr));
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
	int i = 0, j = 0;
	what = malloc(1);
	while(strnow[i] != ' ')
	{
		i++;
	}
	i++;
	while(strnow[i] != ' ')
	{
		d1 += 1;
		what = realloc(what, d1);
		what[j] = strnow[i];
		i++;
		j++;
	}
	i++;
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
	while(strnow[i + 1] != '\0')
        {
                d2 += 1;
                forwhat = realloc(forwhat, d2);
                forwhat[j] = strnow[i];
                i++;
                j++;
        }
	return forwhat;
}

void deleteel(int i, char ** mas, int num)
{
	for(int j = i; j < num - 1; j++)
	{
	 	free(mas[j]);
		mas[j] = malloc(len(mas[j + 1]));
		for(int k = 0; k < len(mas[j]); k++)
		{
			mas[j][k] = mas[j + 1][k];
		}
	}
	mas = realloc(mas, (num - 1)*sizeof(char*));

}
int poisk(char * t, char * w)
{
	printf("jjjjjjjjj\n");
	printf("smth");
	if(len(w) > len(t))
                return 0;
	printf("dddddddd");
        int i, j = 0;
        int p = 0, le = 0;
        int n1 = 0;
        le = len(t);
	printf("%d\n", len(t));
	printf("%d\n", len(w));
        n1 = len(w);
        for(i = 0; i <= le - n1; i++)
        {
		printf("ggggggggg\n");
                p = 0;
                j = 0;
                while((t[i + j] == w[j]) && (j < n1))
		{
			printf("kykykykyykykyky");
                        j++;
                        p = p + 1;
                }
                if(p == n1)
                {
			printf("%d\n_it's_i", i);
			if((i == 0) || (t[i - 1] == ' '))
				if((t[i + j + 1] == ' ') || (t[i + j + 1] == '\0'))
					return 1;
                }

        }
        return 0;


}
char * makeundef(char * str)
{
	char * w = NULL;
	int le = 1;
	for(int i = 6; i < len(str); i++)
	{
		le ++;
		w = realloc(w, le);
		w[i - 6] = str[i];
	}
	w[le] = '\0';
	return w;

}
int pospoisk(char * t, char * w)
{
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
                        if((i == 0) || (t[i - 1] == ' '))
                                if((t[i + j + 1] == ' ') || (t[i + j + 1] == '\0'))
                                        return i;
 		}
        return 0;
	}
}
