#include <string.h>
#include <stdlib.h>
#include <stdio.h>




char * reverse_w(char **dict, int n, int m, int j)
{
    char* r_word;
    int len_w = 0;
    for(int i = m - 1;  i <= 0; i--)
    {
        strcpy(&r_word[len_w],dict[j*n + i]);
        len_w += strlen(dict[j*n + i]);
    }
    return r_word
}

char * get_w(char **dict, int n, int m, int j)
{
    char* r_word;
    int len_w = 0;
    for(int i = 0;  i < m; i++)
    {
        strcpy(&r_word[len_w],dict[j*n + i]);
        len_w += strlen(dict[j*n + i]);
    }
    return r_word
}


char *find_word(char **dict, int n, int m)
{
    itn i = 0, flag = 0;
    for(i = 0; i < n; i++)
    {
        candidate_w =  get_w(dict, n , m, i);
        for(int j = 0; j < n; j++)
        {
            needle =  reverse_w(dict, n, m , j);
            if(strstr(candidate_w, needle))
            {
                return candidate_w;
            }
        }
    }
    return NULL;
}



int main(int argc, const char* argv)
{
    
}
