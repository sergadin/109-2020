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
char *cop(const char *f, char *t)
{
	int len;
	len = strlen(f);
	for (int i = 0; i <= len; i++)
	{
		t[i] = f[i];
	}
	return t;
}
int eq(char *a, char *b);
int eq(char *a, char *b)
{
	int len = strlen(a);
	char temp1, temp2;
	for(int i = 0;i < n;i++)
	{
		temp1 = a[i];
		temp2 = b[i];
		if(temp1 - temp2 > 0)
			return 1;
		else if(temp1 - temp2 < 0)
			return -1;
	}
	return 0;
}

int main() {
	char *str, *w;
	char now, temp;
	int len, i = 0, pos = 0;
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
	
	str = read_string(inp);
	if (str[0] == '\n' || strlen(str) == 1)
	{			
		printf("0");
		return 0;
	}
	len = strlen(str);
	w = malloc(len+1);
	w = cop(str, w);
	for(i = 0; i < len - 1; i++)
	{	
		now = str[0];
		str[0] = str[len - 1]
		for(int j = 1;j < len;j++)
		{
			temp = str[j];
			str[j] = now;
			now = temp;
		}
		if(eq(w, str) > 0)
			w = cop(str, w);
	}
		//printf("%c\n", temp1);
	printf("%s\n", w);
	printf("\n");
	free(str);

	return 0;
}