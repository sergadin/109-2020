#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define LEN 4096
#define MAX_PRINT 12

enum errors {
    SUCCESS,
    READ_ERROR,
    OPEN_ERROR,
    MALLOC_ERROR,
    WRONG_INPUT
};

typedef struct node {
	char* string;
	struct node* next; 
} list;

int read_list(const char* fname, list** head);
void delete_list(list* head);
void print_list(list* head, int n);
