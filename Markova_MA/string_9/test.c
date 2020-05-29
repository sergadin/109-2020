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
	char *str;
	int len, check = 0, i = 6, pos = 0;
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
		/*if (str[0] == '\n') continue;
		len = strlen(str);
		for(i = 0; i < len; i++)
		{
			if(check < 1)
				fprintf(out, "%s", str[i]);
			if(str[i] == '{' && check < 1)
				check++;
			else if(str[i] == '}' && check > 0)
				check--;
		}
		fprintf(out, "/n");*/
		printf("%d", str[i]);
	}
	return 0;
}