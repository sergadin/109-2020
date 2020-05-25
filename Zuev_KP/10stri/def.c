#include"stdio.h"
#include"stdlib.h"
#include"def.h"

int posstr(char * t, char *w);
int dlina(char *t, int k);
int poisk(char * t, char * w, int n1);
int pospoisk(char * t, char * w, int n1);
char *poisku(char * str, char *w);
char *zamena(char * t, char * what, char * forwhat, int n1, int n2);
void delete(int i, char **mas, int n);
int length(const char *s);
char *read_string(FILE *f);
char *strcpy(char *t, const char *s);
int strst(char *t, const char *w, int n);
char *pisk(char *t, char *w, int n, int p);
int dlina(char *t, int k);
                   
void def(FILE *input1, FILE *output, const char *def, const char *und) 
{
	char *hello;
	char *privet;
	char *undef;
	char *strnow;
	char **maswhat = NULL;
	char **masforwhat = NULL;
	int lenmas = 0;
	int num = 0;
	int ind = 0;
	int indec = 0;
	int i, j;
	int l, l1, l2;
	while((strnow = read_string(input1)) != NULL)
	{
		if(strst(strnow, def, length(def)) != 0)
		{
			l = length(strnow);
			l1 = dlina(strnow, 0);
			hello = (char*) malloc((l1)*sizeof(char));
			l2 = l-length(def)-l1-3;
			privet = (char*) malloc((l2)*sizeof(char));
			hello = (char*) realloc(hello, l1+1);
			privet = (char*) realloc(privet, l2+1);
			pisk(strnow, hello, l1, 0);
			pisk(strnow, privet, l2, l1+length(def)-1);
			for(i = 0; i < num; i++)
			{
				if((poisk(maswhat[i], hello, length(hello)) != 0) && (length(maswhat[i]) == length(hello)))
				{
					free(masforwhat[i]);
					masforwhat[i] = malloc(length(privet) + 1);
					for(j = 0; j <= length(privet); j++)
					{
						masforwhat[i][j] = privet[j];
					}
					ind = 1;
				}
			}
			if(ind == 0)
			{
				maswhat = realloc(maswhat, (num + 1)* sizeof(char *));
				masforwhat = realloc(masforwhat, (num + 1) * sizeof(char *));
				num++;
				maswhat[num - 1] = NULL;
				masforwhat[num - 1] = NULL;
				maswhat[num - 1] = realloc(maswhat[num - 1], length(hello) + 1);
				masforwhat[num - 1] = realloc(masforwhat[num - 1], length(privet) + 1);
				for(i = 0; i <= length(hello); i++)
				{
					maswhat[num - 1][i] = hello[i];
				}
				for(i = 0; i <= length(privet); i++)
				{
					masforwhat[num - 1][i] = privet[i];
				}
			}
			free(hello);
			free(privet);
			ind = 0;
		}
		ind = 0;
		if(strst(strnow, und, length(und)) != 0)
		{
			undef = (char*) malloc((length(strnow)-length(und)-1)*sizeof(char));
			undef = poisku(strnow, undef);
			for(j = 0; j < num; j++)
			{
				if((poisk(maswhat[j], undef, length(undef)) != 0) && (length(maswhat[j]) == length(undef)))
				{
					delete(j, maswhat, num); 
					delete(j, masforwhat, num);
					num -= 1;
				}
			}
			free(undef);
		}
		if((strst(strnow, def, length(def)) == 0) && (strst(strnow, und, length(und)) == 0))
		{
			for(i = 0; i < num; i ++)
			{
				if(poisk(strnow, maswhat[i], length(maswhat[i])) != 0)
				{
					//printf("%s\n", maswhat[i]);
					//printf("%d\n", length(maswhat[i]));
					strnow = zamena(strnow, maswhat[i], masforwhat[i], length(maswhat[i]), length(masforwhat[i]));
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
		free(strnow);
	}						
	for(int i = 0; i < num; i ++)
	{
		free(maswhat[i]);
		free(masforwhat[i]);
	}
  	free(maswhat);
	free(masforwhat);
}

int dlina(char *t, int k) //ищет длину hello и privet
{
	int i = k, l = 0, n = 0;
	l = length(t);
	while((t[i] != ' ') && (i <= l))
	{
		i++;
	}
	i++;
	k = i;
	while((t[i] != ' ') && (i < l))
	{
		n++;
		i++;
	}
	return n;	
}

char *pisk(char *t, char *w, int n, int p) //ищет что заменять и на что заменять
{
	int i = p, k = 0, l = 0;
	l = length(t);
	while((t[i] != ' ') && (i <= l))
	{
		i++;
	}
	i++;
	k = i;	
	for(i = k; i < k+n; i++)
	{
		w[i-k] = t[i];
	}
	w[n] = '\0';
	return w;
}

int posstr(char * t, char *w) //ищет позицию слова(любого)
{
        int i, j = 0;
        int p = 0;
        int n1 = 0;
        int le = length(t);
        n1 = length(w);
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

char* zamena(char * strnow, char * what, char * forwhat, int n1, int n2) //заменяет
{
	char * newstr;
	int pos, i, l = 0;
	while(poisk(strnow, what, n1) != 0)
	{
		pos = pospoisk(strnow, what, n1);
		newstr = (char*) malloc((pos+n2+1+length(strnow))*sizeof(char));
		for(i = 0; i < pos; i++)
		{
			newstr[i] = strnow[i];
		}
		for(i = 0; i < n2; i ++)
		{
			newstr[pos + i] = forwhat[i];
		}
		for(i = pos + n1; i <= length(strnow); i ++)
		{
		       	newstr[n2 - n1 + i] = strnow[i];
		}
		newstr[length(newstr)] = '\0';
		strnow = realloc(strnow, length(newstr) + 1);
		strcpy(strnow, newstr);
		free(newstr);	
	}
	return(strnow);
	
}

int poisk(char * t, char * w, int n1) //ищет слово между пробелами
{
	if(length(t) < n1)
		return 0;
	int i, j = 0;
        int p = 0, le = 0;
        le = length(t);
        for(i = 0; i <= le - n1; i++)
        {
                p = 0;
                j = 0;
                while((t[i + j] == w[j]) && (j < n1-1))
		{
                        j++;
                        p = p + 1;
                }
                if(p == n1-1)
                {
			if((i == 0) || (t[i - 1] == ' '))
			{
				if((t[i + n1] == ' ') || (t[i + n1 + 1] == '\0'))
				{
					return 1;
				}
			}
                }

        }
        return 0;


}

char *poisku(char *str, char *w) //#undef
{
	int j = 0;
	for(int i = 7; i < (length(str)-1); i++)
	{
		w[i - 7] = str[i];
		j = j+1;
	}
	w[j] = '\0';
	return w;
}

int pospoisk(char * t, char * w, int n1) //ищет позицию слова между пробелами
{
        int i, j = 0;
        int p = 0, le = 0;
        le = length(t);
        for(i = 0; i <= le - n1; i++)
        {
                p = 0;
                j = 0;
                while((t[i + j] == w[j]) && (j < n1-1))
                {
                        j++;
                        p = p + 1;
                }
                if(p == n1-1)
                {
                        if((i == 0) || (t[i - 1] == ' '))
                        {
                                if((t[i + n1] == ' ') || (t[i + n1 + 1] == '\0'))
                                {
                                        return i;
                                }                          
                        }
                }

        }
        return 0;


}

void delete(int i, char **mas, int n) //удаляет
{
	int j, k;
	for(j = i; j < n - 1; j++)
	{
		free(mas[j]);
		mas[j] = malloc(length(mas[j+1]));
		for(k = 0; k < length(mas[j+1]); k++)
		{
			mas[j][k] = mas[j + 1][k];
		}
	}
	free(mas[n - 1]);
}

int length(const char *s) 
{
	int n = 0;
	while (s[n] != '\0') 
	{
		n++;
	}	
	return n;
}

char *strcpy(char *t, const char *s) 
{
	int n, i; 
	n = length(s);
	for (i = 0; i < n+1; i++) 
	{
		t[i] = s[i];
	}
	return t;
}

char *read_string(FILE *f) 
{
	int l = 0, l1 = 0;	
	char *result;
	char buf[1024];	
	char *s = fgets(buf, 1024, f);
	if(!s) 
		return NULL;
	else
	{
		l = length(s);
		l1 = 0;
		result = (char*) malloc((l + 1)*sizeof(char));
		while(s)
		{
			strcpy(result+l1, s);
			if(s[length(s)-1] == '\n') 
				break;
			s = fgets(buf, 1024, f);
			if (s) 
			{
				l1 = length(s);
				l = l+l1;
				result = (char*) realloc(result, l+1);
			}
		} 
		return result;
	} 
}

int strst(char * t, const char *w, int n) //ищет подстроку в строке
{
	if(n > length(t))
		return 0;
	int i, j = 0;
	int p = 0, l = 0;
	l = length(t);
	for(i = 0; i < l - n; i++) 
	{
		p = 0;
		j = 0;
		while((t[i + j] == w[j]) && (j < n-1))
		{
			j++;	
			p = p + 1;
		}
		if(p+1 == n)
		{
			return 1;
		}
	}
	return 0;	
}

