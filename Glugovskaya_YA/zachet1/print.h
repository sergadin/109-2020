#include <stdio.h>
#include <stdlib.h>
#define Open_Err -1
#define Read_Err -2
#define Not_to_End -3
#define All_Correct 1

void print(char **a, int n, int m);
int print_res_file(char **a, int n, int m, int MinI);
void print_res(char **a, int n, int m, int MinI);