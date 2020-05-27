#include <stdio.h>
#include <stdlib.h>
#define Open_Err -1
#define Read_Err -2
#define Not_to_End -3
#define All_Correct 1

int read(char **a, int n, int m, char *name);
char *Read_Srt(FILE *FileIn);