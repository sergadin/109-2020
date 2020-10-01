#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "f.h"
/*документация
час писала алгоритм оставшееся время пыталась считать строки
похоже не вышло
*/









int main() {
	char *str, ***a;
	int len, i, j, check = -1, ii = -1, jj = -1, n, m, res;
	FILE *inp, *outp;
    if ((inp = fopen("input.txt", "r")) == NULL) {
        printf("ERROR\n");
        return -1;
    }
    if ((outp = fopen("result.txt", "w")) == NULL) {
        printf("ERROR\n");
        fclose(inp);
        return -1;
    }
	if (fscanf(inp, "%d", &n) != 1 || fscanf(inp, "%d", &m) != 1)
        {
            fclose(inp);
			fclose(outp);
			
            return -1;
        }
	a = malloc((n) * sizeof(char **));
    for(int i = 0; i < n; i++)
	a[i] = malloc((m) * sizeof(char*));
    if (read_file(input, a, n, m) == -1)
    {
	
        fclose(outp);
        fclose(inp);
	return -1;
    }
	//printf("здесь кончается считывание\n");
	
	for(i = 0;i < m; i++)
	{
		for(j = 0;j < n;j++)
		{
			if(slen(a[i][j]) == 0)
			{
				check = 1;
				break;
			}
			//str = cop(pol(a[i][j]), str);
			for(int k = j + 1;k < m - 1;k++)
			{
				if(eq(pol(a[i][j]), a[i][k]))
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
	for(i = 0;i < m;i++)
	{
		for(j = 0; j < n; j++)
		{
			if(ii != i && j == jj && slen(a[ii][jj]) != 0)
			{
				fprintf(outp, "%s%s\n", a[i][j], a[ii][jj]);
			}
			else
				fprintf(outp, "%s\n", a[i][j]);
		}
	}
	fclose(outp);
	for (i = 0; i < m;i++)
        {
          for (int j = 0; j < n; j++)
          {
            free(a[i][j]);
          }
          free(a[i]);
        }
    free (a);
	return 0;
}