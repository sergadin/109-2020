#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* int read_file(FILE *file, char ***data, int N, int M)
 * read_file aka функция для считывания файла
 *
 * входные данные:
 *      "двумерный массив строк"
 *      размеры N, M матрицы
 *
 * как делает:
 *      великолепной функцией getline считываем каждую строчку из файла
 * */
int read_file(FILE *file, char ***data, int N, int M)
{
    size_t bufsize = 32;
    for(int i = 0; i < N; i++)
	for(int k = 0; k < M; k++) 
	    data[i][k] = NULL;
    
    for(int i = 0; i < N; i++)
	for(int k = 0; k < M; k++) 
	    
	    if(getline(&data[i][k], &bufsize, file) == -1)
	    {
	         printf("smth wrong with reading \n");
	         return -1;
	    }
    
    //printf("1\n");

    return 0;
}

int find_palindrome(char *word)
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

// i did not come up with algorithm but have an idea
/*int find_palindrome(char **data, int m)
{
    int word1 = 0;
    int letter1 = 0;

    int word2 = m - 1;
    int letter2 = strlen(data[m-1]) - 1;

    int kolvo = 0;
    int len = 0;

    for (int i = 0; i < m; i++)
	len += strlen(word[i]);
    len -= m;


    while ((kolvo < len))
    {
	if(data[word1][letter1] != data[word2][letter2-k])
            //printf("%c %c \n", word[k], word[len-k-1]);
            return -1;
        if(letter1 = strlen(data[word1])-1)
	{
	     word1++;
	     letter1 = 0;
	}
	if(letter2 = 0)
	{
	     word2--;
	     letter1 = strlen(data[word2-1]) - 1;
	}
	kolvo++;
    }
    return 0;
}

*/
//int main(void)
int main(int argc, char *argv[])
{

    int n, m; // size of matrix
    char ***matrix;
    size_t bufsize = 32;
    int check_sum = 0;
    int min = -1;
    FILE *input, *output;

    if (argc != 2)
    {
	printf("wrong arg, try again \n");        
	return -1;
    }
    //input file
    if ((input = fopen(argv[1], "r")) == NULL)
    {
        printf("cannot open input file \n");
        return -1;
    }

    //output file
    if ((output = fopen("result.txt", "w")) == NULL)
    {
        printf("cannot open output file \n");
	fclose(input);
        return -1;
    }
    //reading size of matrix
    if (!(fscanf(input, "%d", &n)) || (n <= 0))
    {
        printf("smth wrong with size \n");
	    fclose(input);
	    fclose(output);
        return -1;
    }

    if(!(fscanf(input, "%d\n", &m)) || (m <= 0))
    {
        printf("smth wrong with size");
        fclose(output);
        fclose(input);
        return -1;
    }
    //creating matrix
    matrix = malloc((n) * sizeof(char **));
    for(int i = 0; i < n; i++)
	matrix[i] = malloc((m) * sizeof(char*));

    //reading
    if (read_file(input, matrix, n, m) == -1)
    {
	
        fclose(output);
        fclose(input);
	return -1;
    }
  
    //trying to fulfill the task

        //find first line with palindromes
//printf("1 \n");
    for(int i = 0; i < n; i++)
    {	
        for(int k = 0; k < m; k++)
        {
	     //printf("%d %d \n", i, k);
             check_sum += find_palindrome(matrix[i][k]);
             //printf("%d \n", find_palindrome(matrix[i][k]));
        }
        if (check_sum == 0)
        {
             min = i;
                 break;
        }
        check_sum = 0;
    }
//printf("1 \n");
    //printf("%d \n", min);
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

    for(int i = 0; i < n; i++)
        for(int k = 0; k < m; k++)
        {

            matrix[i][k] = realloc(matrix[i][k], strlen(matrix[i][k]) + strlen(matrix[min][k]) - 1);
            strcpy(matrix[i][k]+strlen(matrix[i][k])-1, matrix[min][k]);
            matrix[i][k][strlen(matrix[i][k]) + strlen(matrix[min][k]) - 2] = '\0';
            printf("%s \n", matrix[i][k]);
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
