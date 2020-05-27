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


int modify(char **data, int m)
{
    int len1 = strlen(data[0]);
    int current = 0;
    int len = 0;
    
    for(int i = 0; i < m; i++)
	len += strlen(data[i]);
    //printf("%d \n", len - m + 1);

    data[0] = realloc(data[0], len - m + 1);
 
    for(int i = 0; i < m; i++)
    {
//printf("1\n");
printf("%s \n", data[0]);
	strcpy(data[0] + current, data[i]);
//printf("1\n");
        current += (strlen(data[i]) - 1);
    }
    data[0][len - m] = '\0';
    return 0;
}

//int main(void)
int main(int argc, char *argv[])
{

    int n, m; // size of matrix
    char ***matrix;
    size_t bufsize = 32;
    int check_sum = 0;
    int min = -1;
    int len = 0;
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

    if(!(fscanf(input, "%d \n", &m)) || (m <= 0))
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
    // случай матрицы n*1 достаточно просто проверить каждый элемент
    if (m == 1)
    {
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
    }
    // иначе мы делаем вот так
    if (m != 1)
    {
        for(int i = 0; i < n; i++)
        {
             len = strlen(matrix[i][0]);
             modify(matrix[i], m);
             //printf("%s \n", matrix[i][0]);
                 if (find_palindrome(matrix[i][0]) == 0)
             {
                  min = i;
                  matrix[i][0] = realloc(matrix[i][0], len);
                  break;
             }
             matrix[i][0] = realloc(matrix[i][0], len);
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


//sum lines

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
