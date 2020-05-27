#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "f.h"

int main() {
	char *str, ***a;
	int len, i, j, check = -1, ii = -1, jj = -1, n, m, res;
	FILE *inp, *outp;
    if ((inp = fopen("input.txt", "r")) == NULL) {
        printf("ERROR\n");
        return 0;
    }
    if ((outp = fopen("result.txt", "w")) == NULL) {
        printf("ERROR\n");
        fclose(inp);
        return 0;
    }
	if (fscanf(inp, "%d", &n) != 1 || fscanf(inp, "%d", &m) != 1)
        {
            fclose(inp);
			fclose(outp);
			
            return 0;
        }
	res = a_read(inp, a);
	fclose(inp);
	if(res == -1)
	{
		return 0;
	}
	printf("здесь кончается считывание\n");
	
	for(i = 0;i < n; i++)
	{
		for(j = 0;j < m;j++)
		{
			if(slen(a[i][j]) == 0)
			{
				check = 1;
				break;
			}
			//str = cop(pol(a[i][j]), str);
			for(int k = j + 1;k < m - 1;k++)
			{
				if(eq(pol(a[i][j], a[i][k]))
				{
					ii = i;
					jj = j;
					check = 1;
					break;
				}
			}
			if(check)
				break;
		}
	}
	for(i = 0;i < n;i++)
	{
		for(j = 0; j < m; j++)
		{
			if(ii != i && j == jj && strlen(a[ii][jj]) != 0)
			{
				fprintf(outp, "%s%s\n", a[i][j], a[ii][jj]);
			}
			else
				fprintf(outp, "%s\n", a[i][j]);
		}
	}
	fclose(outp);
	for (i = 0; i < n;i++)
        {
          for (int j = 0; j < m; j++)
          {
            free(a[i][j]);
          }
          free(a[i]);
        }
    free (a);
	return 0;
}