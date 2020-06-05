#include<stdio.h>
#include<string.h>
#include <stdlib.h>

int if_symbols(FILE * output, int count_sym, int limit, char c) ;
int if_letter(FILE *output, int word_len, int limit, int count_sym, char buff[1024] ,int start_w, int finish_w, char c) ;
void file_print_word(FILE *output, char buff[1024], int start_w, int finish_w);
int solve_one (FILE *output, FILE *input);
