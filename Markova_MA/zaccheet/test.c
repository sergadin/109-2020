#include <stdlib.h>
#include <stdio.h>


int main(void)
{
	int i,j,n,m,len = 32;
    char ***a;
    char buf[len];
    FILE *fp;
    scanf("%d %d", &m, &n);
    fp = fopen("input.txt", "r");
    if (!fp)
    {
    	return -1;
    }
    //make memory
    a = (char ***)malloc(m*sizeof(char **));
    if (!a)
    {
    	fclose(fp);
    	return -1;
    }
    for (i = 0; i < m; i++)
    {
    	a[i] = (char **)malloc(n*sizeof(char *));
    	if (!a[i])
    	{
    		fclose (fp);
    		for (j = 0; j < i; j++)
    			free(a[j]);
    		free(a);
    		return -1;
    	}
    }


    //input
    for (i = 0; i < m; i++)
    {
    	for (j = 0; j < n; j++)
    	{
    	    int q,p;
    	    if (!fgets(buf,len,fp))
            {
				//error
                return -1;
            }
            for (q = 0; buf[q]; q++)
            {
                if (buf[q] == '\n')
                {
                    buf[q] = '\0';
                    break;
                }
            }
            a[i][j] = (char *)malloc(q+1);
            if (!a[i][j])
            {
				//error
                return -1;
            }
            for (p = 0; p <= q; p++)
                a[i][j][p] = buf[p];
    	}
    }
    //output
    for (i = 0; i < m; i++)
    {
    	for (j = 0; j < n; j++)
    	{
    		printf("%s\n", a[i][j]);
    	}
    }
    //cleaning of memory

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            free(a[i][j]);
        }
    	free(a[i]);
    }
    free(a);
    fclose(fp);


    return 0;
}
