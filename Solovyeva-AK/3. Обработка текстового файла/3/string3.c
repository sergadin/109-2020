#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


char *read_string(FILE *in) {
	char buf[1024];
	char *s = fgets(buf, 1024, in);
	if(s) {
		int len = strlen(s);
		int tmp = 0;
		char *res = malloc(len+1);
		while(s) {
			strcpy(res+tmp, s);
			if(s[strlen(s)-1] == '\n') break;
			s = fgets(buf, 1024, in);
			if (s) {
				tmp = strlen(s);
				len += tmp;
				res = realloc(res, len+1);
			}
		}
		return res;
	}
	return NULL;
}

int main(void){
    FILE *inp, *out;
    char *str;
    int flag = 0;

    if ((inp = fopen("input.txt", "r")) == NULL) {
        printf("ERROR\n");
        return -1;
    }
    
    if ((out = fopen("output.txt", "w")) == NULL) {
        printf("ERROR\n");
        fclose(inp);
        return -1;
    }

	int flag1 = 0, flag2 = 0;
	while(str = read_string(inp)){
		if(flag2) {
			fprintf(out, "\n");
		}
		flag2 = 1;
		int len = strlen(str);
		for(int i = 0; i < len; i++) {
			if(str[i] == ' ') {
				while(str[i] == ' ') {
					i++;
				}
				if(flag1){
					fprintf(out, "\n");
				}
				i--;
			} else {
				if(str[i] != '\n') {
					fprintf(out, "%c", str[i]);
					flag1 = 1;
				}
			}
		}
		free(str);
	}    
	fclose(inp);
	fclose(out);
	return 0;
}
