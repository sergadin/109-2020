#include <string.h>
#include <stdlib.h>
#include <stdio.h>


struct data
{
    char** array;
    int n;
    int m;
};

int find_substring(struct data A, int heap, int needle);
char *create_dictionary(struct data A, int i);
int change(struct data *A, int word);
int delete_char(struct data *A, int i, int j, char *dict);
int find_word(struct data A);
int func(struct data *A);
void free_array(struct data *A);
int read_data(FILE *file,struct data *A);



int find_substring(struct data A, int heap, int needle)
{
    int count = 0; // number of 0s in heap
    while(count < A.m)
    {
        if(A.array[heap * A.m] == 0)
        {
            count++;
            A.array[heap*A.m]++;
            continue;
        }
        if(A.array[heap * A.m] == (A.array[needle * A.m + 1] - 1)) // A.array[needle*A.m + 1] - 1 is the last char of line needle
        {
            int flag = 1;
            int num = 0; // number of 0s in needle
            int shift = 2;
            A.array[heap * A.m]++;
            while(count < A.m  && num < A.m)
            {
                if(A.array[heap * A.m] == 0)
                {
                    count++;
                    A.array[heap]++;
                    continue;
                }
                
                if(A.array[needle * A.m + 1] == 0)
                {
                    num++;
                    shift++;
                    continue;
                }
                
                if(A.array[heap * A.m] != A.array[needle * A.m + 1] - shift)
                {
                    flag = 0;
                    break;
                }
                shift++;
                
            }
            if(flag)
            {
                return 1;
            }
        }
        A.array[heap * A.m]++;
    }
    return 0;
}



char *create_dictionary(struct data A, int i)
{
    char dict[256];
    int len_d = 0;
    
    for(int j = 0; j < 256; j++)
    {
        dict[i] = 0;
    }
    
    for(int j = 0; j < A.m; j++)
    {
        int len = strlen(A.array[i * A.m + j]);
        for(int h = 0; h < len; h++ )
        {
            if(!strchr(dict, A.array[i * A.m + j][h]))
            {
                dict[len_d] = A.array[i * A.m + j][h];
                len_d++;
            }
        }
    }
    
}


int change(struct data *A, int line)
{
    char *dict = create_dictionary(*A, line);
    
    

    for(int  i = 0; i < A->n; i++)
    {
        
        for(int j = 0; j < A->n; j++)
        {
            int temp = delete_char(A, i, j, dict);
            if(!temp)
            {
                return -1;
            }
        }
    }
    
    return 0;
     
}

int delete_char(struct data *A, int i, int j, char *dict)
{
    int len = strlen(A->array[i * A->m + j]);
    for(int h = 0 ; h <  len; h++)
    {
        if( !strchr(dict, A->array[i * A->m +j][h]) )
        {
            for(int l = h ; l < len - 1; l++)
            {
                A->array[i * A->m + j][h] = A->array[i * A->m + j][h + 1];
            }
            
            if( !(A->array[i * A->m + j] = realloc(A->array[i * A->m + j], (len - 1) *sizeof(char*))) )
            {
                return -1;
            }
        }
    }
    return 0;
}


int find_word(struct data A)
{
    int i = 0;
    for(i = 0; i < A.n; i++)
    {
        for(int j = 0; j < A.n; j++)
        {
            int temp =  find_substring(A, i ,j);
            if(temp)
            {
                return i;
            }
        }
    }
    return -1;
}



int func(struct data *A)
{
    int found_w =  find_word(*A);
    if(found_w == -1)
    {
        return -1;
    }
    
    change(A, found_w);
}



int read_data(FILE *file,struct data *A)
{
    size_t buf = 32;


    for(int i = 0; i < A->n; i++)
    {
        for(int j = 0; j < A->m; j++)
        {
            A->array[i * A->m + j] = NULL;
            if(getline(&A->array[i * A->m + j],&buf,file) == -1)
            {
                return -1;
            }
        }
    }
    return 0;
}


void free_array(struct data *A)
{
    for(int i = 0; i < A->n * A->m; i++)
    {
        free(A->array[i]);
    }
    free(A->array);
}




int main(int argc, const char** argv)
{
    FILE *input, *output;
    struct data A;
    int stat;
    char * name_of_input, name_of_output;
    
    if( (argc != 3) )
    {
        fprintf(stderr, "Usage: %s [name of input file] [name of output file]\n", argv[0]);
        return -1;
    }
    
    name_of_input = argv[1];
    name_of_output = argv[2];
    
    if( !(input = fopen(name_of_output, "r")) )
    {
        fprintf(stderr, "ERROR can't open %s\n",name_of_output );
        return -1;
    }
    
    if( !(output = fopen(name_of_output, "r")) )
    {
        fprintf(stderr, "ERROR can't open %s\n",name_of_output );
        fclose(input);
        return -1;
    }
    
    if(!fscanf(input, "%d", &A.n))
    {
        fprintf(stderr, "ERROR can't read %s\n",name_of_input );
        fclose(input);
        fclose(output);
        return -1;
    }
    
    if(!fscanf(input, "%d", &A.m))
    {
        fprintf(stderr, "ERROR can't read %s\n",name_of_input );
        fclose(input);
        fclose(output);
        return -1;
    }
    
    if( !(a = (char**)malloc(A.n * A.m * sizeof(char*))) )
    {
        fprintf(stderr, "Memory ERROR!\n");
        return -1;
    }
    
    
    stat = read_data(input, &A);
    
    if(stat != 0)
    {
        switch(error)
        {
            case -1:
                fprintf(stderr, "ERROR can't read element from %s\n", name_of_input);
                free_array(&A);
                fclose(input);
                fclose(output);
                return -1;
        }
    }
    
    printf("read array:\n");
    fprintf(output,"read array:\n");
    for(int i = 0; i < A.n * A.m; i++)
    {
        fprintf(output, "%s\n"A.array[i]);
        printf("%s\n"A.array[i]);
    }
    
    stat = find_word(&A);
    f(stat != 0)
    {
        switch(error)
        {
            case -1:
                fprintf(stderr, "ERROR can't find sti\ring\n")
                free_array(&A);
                fclose(input);
                fclose(output);
                return -1;
        }
    }
    
    printf("changed array:\n");
    fprintf(input,"cahnged array:\n");
    for(int i = 0; i < A.n * A.m; i++)
    {
        fprintf(output, "%s\n"A.array[i]);
        printf("%s\n"A.array[i]);
    }
    
    free_array(&A);
    fclose(input);
    fclose(output);
    return 0;
    
}
