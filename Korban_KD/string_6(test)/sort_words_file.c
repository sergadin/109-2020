#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort_words_file.h"

#define NUM 1024



struct dictionary sort_words_file(FILE *file , int *error)
{
    char c;
    int len_b = 0, len_w = 0;
    char buf[NUM + 1],  *word = NULL;
    struct dictionary dict;
    
    dict.words = NULL;
    dict.size = 0;
    dict.len_d = 0;

    buf[0] = 0;
    
    if(fscanf(file, "%c", &c) != 1)
    {
        if(feof(file))
        {
            *error = INPUT_ERROR;
            return dict;
        }
        else
        {   
            *error = READ_ERROR;
            return dict;
        }
    }
    
    do
    {
        if( (c != '\0') && (c != '\n') && (c != '\r') && (c != ' ') && (c != '\t')) //reading word from file 
        {
            if(len_b < NUM)
            {
                buf[len_b] = c;
                len_b++;
                buf[len_b] = 0;
            }
            else
            {
                word = realloc(word, (len_w + NUM + 1)*sizeof(char));
                strcpy(&word[len_w], buf);
                len_w += NUM;
                len_b = 0;
                buf[0] = 0;
            }
        }
        else
        {
            
            if( (len_w > 0) || (len_b > 0) ) //word ended
            {
                int temp;
                
                if(len_b != 0)
                {
                    word = realloc(word, (len_w + strlen(buf) + 1)*sizeof(char));
                    strcpy(&word[len_w], buf);
                    buf[0] = 0;
                }
                
                len_w += len_b;
                
                
                temp = str_put_in_dictionary(&dict, word, len_w);
                
                if(temp < 0)
                {
                    switch(temp)
                    {
                        case -1:
                            *error = MEMORY_ERROR;
                            return dict;
                    }
                }
                
                len_w = 0;
                len_b = 0;
                free(word);
                word = NULL;
                
                
            }
        }
    }while(fscanf(file, "%c", &c) == 1);
    
    
    if(!feof(file))
    {
        *error = READ_ERROR;
        return dict;
    }
    
    dict.words = realloc(dict.words, ( dict.len_d )*sizeof(char*) );
    
    error = 0;
    
    free(word);
    fclose(file);
    return dict;
}







int str_put_in_dictionary(struct dictionary *dict, char *word, int len_w)
{
    int i = 0;
    
    if( dict->len_d >= dict->size )
    {
        dict->words = realloc(dict->words, ( dict->size + 10)*sizeof(char*) );
        dict->size += 10;
    }
    
    for(i = 0; i < dict->len_d; i++)// putting word in dictionary
    {
        int val = strcmp(dict->words[i], word);
        if(val > 0) // found place where to put word
            break;
        if(val == 0) // found same word in dictionary
        {
            return 0;
        }
    }
    
    if( !(dict->words[dict->len_d] = (char*)malloc( (len_w + 1)*sizeof(char))) )
    {
        return -1;
    }
    
    strcpy(dict->words[dict->len_d], word);
    
    for(int j = dict->len_d ; j > i; j--)// puts dict.words[dict.len_d] in correct position
    {
        char *temp = dict->words[j];
        dict->words[j] = dict->words[j - 1];
        dict->words[j - 1] = temp;
    }
    dict->len_d++;
    return 1;
}


