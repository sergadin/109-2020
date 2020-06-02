#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *read_string(FILE *in) {
    char buf[1024];
    char *s = fgets(buf, 1024, in);
    if(s) {
        int len = strlen(s);
        int tmp = 0;
		int past_len = 0;
        char *res = malloc(len+1);
        while(s) {
            strcpy(res + past_len, s);
            if(s[strlen(s)-1] == '\n') break;
            s = fgets(buf, 1024, in);
            if (s) {
                tmp = strlen(s);
					past_len = len;
                len += tmp;
                res = realloc(res, len+1);
            }
        } 
        return res;
    } 
    return NULL;
}
char *cop(const char *f, char *t, int pos, int len_word)
{
	for (int i = 0; i < len_word; i++)
	{
		t[i] = f[pos + i];
	}
	return t;
}
int eq(char *w,char *stock, int len_word)
{
	int len = strlen(stock), check = 0;
	for(int i = 0;i < len;i++)
	{
		if(stock[i] == '\n')
		{
			if(check < strlen(w) )
				check = 0;
			else
				return 0;
		}
		else
		{
			if(stock[i] == w[check])
				check++;
			else if(check != 0)
				check = 0;
		}
	}
	return 1;
	
}
//int eq(char *a, char *b)

int main() {
	char *str, *w = NULL, *stock = NULL;
	int len, i = 0, len_word = 0, pos = 0, len_stock = 0;
	FILE *inp, *out;
    if ((inp = fopen("input.txt", "r")) == NULL) {
        printf("ERROR\n");
        return 0;
    }
    if ((out = fopen("out.txt", "w")) == NULL) {
        printf("ERROR\n");
        fclose(inp);
        return 0;
    }
	stock = malloc(stock, len_word + 1);
	stock[0] = '\n';
	while (str = read_string(inp)) 
	{
		if (str[0] == '\n') continue;
		len = strlen(str);
		for(i = 0;i < len;i++)
		{
			if(str[i] == '\n' || str[i] == ' ')
			{
				if(len_word == 0)
					continue;
				w = malloc(len_word + 1);
				w = cop(str, w, pos, len_word);
				if(eq(w, stock, len_word))
				{
					len_stock += len_word;
					stock = realloc(stock, len_stock + 1);
					stock[len_stock + 1] = '\n';
					for(int j = 0; j < len_word;j++)
					{
						stock[len_stock - len_word - 1 + j] = w[j];
					}
				}
				free(w);
			}
			else
				len_word++;
		}
		//i = 2;
		//m = str[i];
		//putchar(str[i]);
		//printf("%s\n", m);
		printf("%s\n", stock);
		//printf("\n");
		free(str);
	}
	return 0;
}