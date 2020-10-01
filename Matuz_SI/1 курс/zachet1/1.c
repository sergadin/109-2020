#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_file(FILE *file, char ***data, int N, int M)
{
    size_t bufsize = 32;

    
    for(int i = 0; i < N; i++)
	for(int k = 0; k < M; k++) 
	{
	    data[i][k] = NULL;
	    if(getline(&data[i][k], &bufsize, file) == -1)
	    {
	         printf("smth wrong with reading \n");
	         return -1;
	    }
	}
    
    //printf("1\n");
    return 0;
}

int is_palindrome(char *word)
{
    int len = strlen(word) - 1;
    for(int k = 0; k < len/2; ++k)
    {
        if(word[k] != word[len-k-1])
        {
	   //printf("%c %c \n", word[k], word[len-k-1]);
	   return -1;
        }
    }
    return 0;
}
    
int main(int argc, char *argv[])
{
    int n, m; // size of matrix
    char ***matrix;
    char *buff;
    FILE *input, *output;
    int min = -1;
    int len = 0;
    int word_len = 0;
    int line_len = 0;
    int current = 0;

    if ((input = fopen(argv[1], "r")) == NULL)
    {
        printf("cannot open input file \n");
        return -1;
    } 

    if ((output = fopen("result.txt", "w")) == NULL)
    {
        printf("cannot open output file \n");
	fclose(input);
        return -1;
    }
    if (!(fscanf(input, "%d", &n)) || (n <= 0))
    {
        printf("smth wrong with size \n");
	fclose(input);
	
        return -1;
    }

    if(!(fscanf(input, "%d \n", &m)) || (m <= 0))
    {
        printf("smth wrong with size");

        fclose(input);
        return -1;
    }

    matrix = malloc((n) * sizeof(char **));
    for(int i = 0; i < n; i++)
	matrix[i] = malloc((m) * sizeof(char*));

    //reading
    if (read_file(input, matrix, n, m) == -1)
    {
        fclose(input);
	return -1;
    }
    //case matrix n*1
    if (m == 1)
    {
        for(int i = 0; i < n; i++)	
        {
            if (is_palindrome(matrix[i][0]) == 0)
            {
	         //printf("%d \n", is_palindrome(matrix[i][0]));
                 min = i;
                 break;
            }
	}
    }


    if (m != 1)
    {
	for(int i = 0; i < n; i++)
	{
	    for(int k = 0; k < m; k++)
	        line_len += strlen(matrix[i][k]);
	   // printf("1111 %d\n", line_len);
            if (matrix[i][m-1][strlen(matrix[i][m-1])-1] != '\n')
	    {
//case last word in line without '\n'
//printf("11111111\n");
                word_len = strlen(matrix[i][0]);
		matrix[i][0] = realloc(matrix[i][0], line_len-m+3);
                current = 0;
                for(int k = 1; k < m; k++)
	        {
		    current += strlen(matrix[i][k-1]);
		    strncpy(matrix[i][0] + current-1, matrix[i][k], strlen(matrix[i][k])-1);
		    current -= 1;
	        }
		matrix[i][0][line_len-m] = matrix[i][m-1][strlen(matrix[i][m-1])-1];
		matrix[i][0][line_len-m+1] = '\n';
		matrix[i][0][line_len-m+2] = '\0';
                
                if (is_palindrome(matrix[i][0]) == 0)
		{
		    matrix[i][0] = realloc(matrix[i][0], word_len+1);
		    matrix[i][0][word_len-1] = '\n';
		    matrix[i][0][word_len] = '\0';
                    min = i;
                    break;
                }
		printf("%s", matrix[i][0]);
//return back
		matrix[i][0] = realloc(matrix[i][0], word_len+1);
		matrix[i][0][word_len-1] = '\n';
		matrix[i][0][word_len] = '\0';
		//printf("%s", matrix[i][0]);
                
   
	    } else
	    {
                word_len = strlen(matrix[i][0]);
	        matrix[i][0] = realloc(matrix[i][0], line_len-m+4);
                current = 0;

                for(int k = 1; k < m; k++)
	        {
		    if(matrix[i][k][0] != '\n')
		    {
		        current += strlen(matrix[i][k-1]);
                        //printf("%d %d \n", current, current -1);
		        strncpy(matrix[i][0] + current-1, matrix[i][k], strlen(matrix[i][k])-1);
                        current -= 1;
                    }    
	        }
		
		matrix[i][0][line_len-m] = '\n';
	        matrix[i][0][line_len-m+1] = '\0';
     		//printf("%s", matrix[i][0]);

 		if (is_palindrome(matrix[i][0]) == 0)
		{
		    matrix[i][0] = realloc(matrix[i][0], word_len+1);
		    matrix[i][0][word_len-1] = '\n';
		    matrix[i][0][word_len] = '\0';
                    min = i;
                    break;
                }

		matrix[i][0] = realloc(matrix[i][0], word_len+1);
		matrix[i][0][word_len-1] = '\n';
		matrix[i][0][word_len] = '\0';
		//printf("%s", matrix[i][0]);
	    }
	    line_len = 0;
      }

    }
    if (min == -1)
    {
        printf("nothing to do because there is no palindromes \n");
        for(int i = 0; i < n; i++) 
        {
             for(int k=0; k < m; k++)
                      free(matrix[i][k]);
             free(matrix[i]);
        }
        free(matrix);
        fclose(output);
        fclose(input);
        return -1;
    }

    //printf("%d \n", min);
    //sum lines
    for(int i = 0; i < n; i++)
        for(int k = 0; k < m; k++)
        {
	    current = strlen(matrix[i][k]);
	    len = strlen(matrix[i][k])+strlen(matrix[min][k]);
            matrix[i][k] = realloc(matrix[i][k], len );
            strncpy(matrix[i][k] + current-1, matrix[min][k], strlen(matrix[min][k])-1);
	    matrix[i][k][len - 2] = '\n';
	    matrix[i][k][len - 1] = '\0';
                
            
        }


    //printing result
    for(int i = 0; i < n; i++) 
    {
	for(int k=0; k < m; k++)
	     fprintf(output, "[%d][%d] = %s",i, k, matrix[i][k]);
	fprintf(output, "\n");
    }

    //cleaning
    for(int i = 0; i < n; i++) 
    {
	for(int k=0; k < m; k++)
             free(matrix[i][k]);
	free(matrix[i]);
    }
    free(matrix);

    fclose(output);
    fclose(input);

    return 0;
}


  

        