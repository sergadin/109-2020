#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prog3-6.h"

char **sort_file(FILE* input)
{
    char **word_arr;
    char sym_buffer;
    char *word_buffer;
    int word_count = 0;
    int sym_count = 0;
    int I, J;
    int w_arr_size = 1;
    int s_arr_size = 1;
    word_arr = (char**)malloc(w_arr_size * sizeof(char*));
    word_arr[0] = (char*)malloc(s_arr_size * sizeof(char));
    word_arr[0][0] = 0;

    while ((fscanf(input, "%c", &sym_buffer) == 1))
    {
        if ((sym_buffer != ' ') && (sym_buffer != '\n') && (sym_buffer != '    '))
        {
            if ((sym_count + 2) > s_arr_size)
            {
                s_arr_size += 1;
                word_arr[word_count] = (char*)realloc(word_arr[word_count], s_arr_size * sizeof(char));
            }
            word_arr[word_count][sym_count] = sym_buffer;
            sym_count++;
            word_arr[word_count][sym_count] = 0;
        }
        else
            if (sym_count > 0)
            {
                if ((word_count + 2) > w_arr_size)
                {
                    w_arr_size += 1;
                    word_arr = (char**)realloc(word_arr, w_arr_size * sizeof(char*));
                }
                word_count++;
                s_arr_size = 1;
                sym_count = 0;
                word_arr[word_count] = (char*)malloc(s_arr_size * sizeof(char));
                word_arr[word_count][0] = 0;
            }
    }

    if (sym_count > 0)
    {
        word_arr = (char**)realloc(word_arr, (word_count + 2) * sizeof(char*));
        word_count++;
        sym_count = 0;
        word_arr[word_count] = (char*)malloc(1 * sizeof(char));
        word_arr[word_count][0] = 0;
    }

    I = word_count - 1;

    while (I > 0)
    {
        J = 0;
        while (J < I)
        {
            if (strcmp(word_arr[J], word_arr[J + 1]) > 0)
            {
                word_buffer = word_arr[J];
                word_arr[J] = word_arr[J + 1];
                word_arr[J + 1] = word_buffer;
            }
            J++;
        }
        I--;
    }

    return word_arr;
}
