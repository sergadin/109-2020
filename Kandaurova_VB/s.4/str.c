#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"

char *readstring(FILE *input);

void findstr(FILE *input, FILE *output, char *w)  {
	int N = 0, wlen, id, i, j;
	char *s, *now, *str;
	wlen = strlen(w);
	while ((s = readstring(input)) != NULL) {
		int nowlen, slen = strlen(s);
		N++;
		now = s;    
        nowlen = slen;
		while (nowlen > 0) {
            for (i = 0; i <= nowlen - wlen; i++) {
                id = 1;
		        for (j = 0; j < wlen; j++) {
			        if (now[i + j] != w[j]) {
				        id = 0;
			  	        break;
			        }
                }
		        if (id == 1) {
                    fprintf(output, "%d %d\n", N, i + 1);
			        str = (char *)now + i;
		        }
                str = NULL;
	        }
            if(str == NULL)
                break;
			now = str + wlen;
            nowlen = strlen(now);
		}
		free(s);
	}
}

char *readstring(FILE *f) {
	char buf[1024];
	buf[0] = 0;
	char *s = fgets(buf, 1024, f);
	if(s) {
		int len = strlen(s);
		char *result = malloc(len + 1);
		strcpy(result, s);
		return result;
	}
	return NULL;
}
