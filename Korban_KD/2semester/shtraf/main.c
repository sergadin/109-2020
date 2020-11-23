#include <string.h>
#include <stdio.h>

int find_min(char* string);


int find_min(char* string)
{
    int len = strlen(string);
    int min = 0;
    
    for(int i = 1; i < len; i++ )
    {
        for(int j = 0; j < len; j++)
        {
            if(string[(j + len - min)%len] > string[(j + len - i)%len])
            {
                min = i;
                break;
            }
            if(string[(j + len - min)%len] < string[(j + len - i)%len])
            {
                break;
            }

        }
    }
    return min;
}


int main(int argc, char** argv)
{
    char *string;
    int res;
    if( (argc != 2) )
    {
        fprintf(stderr, "Usage: %s [string]\n", argv[0]);
        return -1;
    }
    string = argv[1];
    res = find_min(string);
    (void)res;
    printf("%d %d\n", res, 2%2);
    return 0;
}



