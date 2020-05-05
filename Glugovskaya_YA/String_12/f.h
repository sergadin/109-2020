#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define ERROR_OPEN_A -1
#define ERROR_OPEN_B -2
#define ERROR_READ_A -3
#define MAX_IT 1e15

int Formating(const char *fileIn, const char *fileOut, int Start, int End);
int Count_Strings (const char *fileIn);
int Count_El_InString(const char *fileIn, int *Count_El, int count_strings);