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

//int eq(char *a, char *b)

int main() {
	char *str, *m;
	int len, check = 0, i = 0, pos = 0;
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
	while (str = read_string(inp)) 
	{
		if (str[0] == '\n') continue;
		len = strlen(str);
		for(i = 0; i < len; i++)
		{
			if(check)
			{
				if(str[i] == '}')
				{
					check = 0; 
					putchar(str[i]);
					//str[i - pos] = str[i];
				}
			}
			else 
			{
				putchar(str[i]);
				if(str[i] == '{')
				{
					check = 1;
				}
			}
			//str[i - pos] = str[i];
		}
		pos = 0;
		//i = 2;
		//m = str[i];
		//putchar(str[i]);
		//printf("%s\n", m);
		//printf("%s\n", str);
		printf("\n");
		free(str);
	}
	return 0;
}