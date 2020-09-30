#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_string(FILE *in);
void print_matrix(char **matrix, int n, int m, FILE * out);
void read_matrix(char **matrix, FILE *inp, int n);
int search(char **matrix, int n, int m);
void sum(char **matrix, int n, int m, int k);
