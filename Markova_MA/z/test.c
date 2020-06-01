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
	len = slen(f);
	for (int i = 0; i <= len; i++)
	{
		t[i] = f[i];
	}
	return t;
}
//int eq(char *a, char *b)

int main() {
	char *str, *w = NULL;
	char temp1;
	int len, i = 0, word = 0;
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
	
	str = read_string(inp)) 
	if (str[0] == '\n' || strlen(str) == 1)
	{			
		printf("0");
		return 0;
	}
	len = strlen(str);
	w = malloc(len);
	w = cop(str, w);
	//for(i = 1;i < len - 1;i++)
	//{
		temp1 = str[0];
		/*for(j = 0; j < len; j++)
		{
			temp2 = 
			str[j + 1] = str[i];
			tmp = 
		}*/
	//}
		//i = 2;
		//m = str[i];
		//putchar(str[i]);
		printf("%c\n", temp1);
		printf("%s\n", w);
		//printf("\n");
		free(str);

	return 0;
}