#include"stdio.h"
#include"stdlib.h"
#include"def.h"
int length(const char *s);
char *read_string(FILE *f);
char *strcpy(char *t, const char *s);
char *zamena(char *t, const char *hello, const char *privet, int k); 
int strst(char *t, const char *w);
int poisk(char * t, const char *w);
char *pisk(char *t, char *w, int n, int p);
int dlina(char *t, int k);

void def(FILE *input1, FILE *output, const char *def, const char *und)
{
	char *s;
	char *t;
	char *hello; 
	char *privet; 
	int l, l1, l2, i;
	while((s = read_string(input1)) != NULL)
	{ 
		while((s) && (strst(s, def) == 0))
		{			
			l = length(s);
			t = (char*) malloc((l + 1)*sizeof(char));
			strcpy(t, s);
			fprintf(output, "%s\n", t);
			free(s);
			s = read_string(input1);
			free(t);
		}
		if(s)
		{
			l1 = dlina(s, 0);
			hello = (char*) malloc((l1)*sizeof(char));		
			l2 = dlina(s, l1+length(def)+1);
			l2 = l2-2;
			privet = (char*) malloc((l2)*sizeof(char));
			pisk(s, hello, l1, 0);
			pisk(s, privet, l2, l1+length(def)+1);
			free(s);
			s = read_string(input1);
			l = length(s); 
			t = (char*) malloc((l + 1)*sizeof(char));
			l1 = length(hello); 
			l2 = length(privet);
			while(s)
			{

				if (strst(s, und) != 0)
				{
					break;
				}
				strcpy(t, s);
				while (strst(t, hello) != 0)
				{
					l = l+l1;
					t = (char*) realloc(t, l);
					i = poisk(t, hello);
					zamena(t, hello, privet, i);		
				}
				fprintf(output, "%s\n", t);	
				free(s);
				s = read_string(input1);
				free(t);
			}
			free(hello);
			free(privet);
			free(t);
		}
	}
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
	while((t[i] != ' ') && (i <= l))
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
	return w;
}

char *zamena(char *t, const char *hello, const char *privet, int k) //заменяет hello на privet
{
	int i = 0, l = 0, l1 = 0, l2 = 0;	
	l = length(t);
	l1 = length(hello);
	l2 = length(privet);
	while((t[i] != '\0') && (i <= length(t)))
	{
		if(i == k)
		{
			for(i = l-(l2-l1)-1; i >= k+l1; i--)
			{
				t[i+(l2-l1)] = t[i];
				
			}
			for(i = k; i < k+l2; i++)
			{
				t[i] = privet[i-k];
			}
		}
		i++;
	}
	return t;	
}

int poisk(char *t, const char *w) //ищет столбец в котором находится hello
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

int length(const char *s) 
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

int strst(char * t, const char *w) //ищет подстроку в строке
{
	if(length(w) > length(t))
		return 0;
	int i, j = 0;
	int p = 0, l = 0;
	int n = 0;
	l = length(t);
	n = length(w);
	for(i = 0; i < l - n; i++) 
	{
		p = 0;
		j = 0;
		while((t[i + j] == w[j]) && (j < n))
		{
			j++;	
			p = p + 1;
		}
		if(p == n)
		{
			return 1;
		}

	}
	return 0;	
}

