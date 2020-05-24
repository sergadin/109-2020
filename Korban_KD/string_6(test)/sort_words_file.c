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
    
    
    if( !(dict.words = (char**)malloc(10*sizeof(char*))) )
    {
        *error = 3;
        dict.words = NULL;
        return dict;
    }
    
    dict.size = 10;
    
    if( !(dict.words[0] = (char*)malloc(1*sizeof(char))) )
    {
        *error = 3;
        dict.words = NULL;
        return dict;
    }
    
    dict.words[0][0] = 0; // after each word dict.words[ dict.len_d ] is always '\0'
    dict.len_d = 0; // number of words 
    
    buf[0] = 0;
    
    while(fscanf(file, "%c", &c) == 1)
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
                
                if( dict.len_d + 1 >= dict.size )
                {
                    dict.words = realloc(dict.words, ( dict.size + 10)*sizeof(char*) );
                    dict.size += 10;
                }
                
                temp = str_put_in_dictionary(&dict, word, len_w);
                
                if(temp < 0)
                {
                    switch(temp)
                    {
                        case -1:
                            printf("Memory cheack was not done (dict.len_d + 1) should be  < (dict.size)\n");
                            *error = 3;
                            dict.words = NULL;
                            return dict;
                        case -2:
                            *error = 3;
                            dict.words = NULL;
                            return dict;
                    }
                }
                
                len_w = 0;
                len_b = 0;
                free(word);
                word = NULL;
                
                
            }
        }
    }
    
    // word may be last in file [e.g 'word''eof' ]
    if( (len_w > 0) || (len_b > 0) )
    {
        int temp;
                
        if(len_b != 0)
        {
            word = realloc(word, (len_w + strlen(buf) + 1)*sizeof(char));
            strcpy(&word[len_w], buf);
            buf[0] = 0;
        }
                
        len_w += len_b;
                
        if( dict.len_d + 1 >= dict.size )
        {
            dict.words = realloc(dict.words, ( dict.size + 1)*sizeof(char*) );
            dict.size += 1;
        }
                
        temp = str_put_in_dictionary(&dict, word, len_w);
                
        if(temp < 0)
        {
            switch(temp)
            {
                case -1:
                    printf("Memory cheack was not done (dict.len_d + 1) should be  < (dict.size)\n");
                    *error = 3;
                    dict.words = NULL;
                    return dict;
                case -2:
                    *error = 3;
                    dict.words = NULL;
                    return dict;
            }
        }
    }
    
    if(!feof(file))
    {
        *error = 2;
        dict.words = NULL;
        return dict;
    }
    
    
    
    dict.words = realloc(dict.words, ( dict.len_d + 1)*sizeof(char*) );
    
    error = 0;
    
    free(word);
    fclose(file);
    return dict;
}







int str_put_in_dictionary(struct dictionary *dict, char *word, int len_w)
{
    
    if( dict->len_d + 1 >= dict->size )
    {
        return -1;
    }
    
    for(int i = 0; i < dict->len_d + 1; i++)// putting word in dictionary
    {
        int val = strcmp(dict->words[i], word);
        if(val > 0) // find place where to put word
        {
            
            if( !(dict->words[dict->len_d + 1] = (char*)malloc( (len_w + 1)*sizeof(char))) )
            {
                return -2;
            }
            
            strcpy(dict->words[dict->len_d + 1], word);

            for(int j = dict->len_d + 1 ; j > i; j--)// puts dict.words[dict.len_d + 1] in correct position
            {
                char *temp = dict->words[j];
                dict->words[j] = dict->words[j - 1];
                dict->words[j - 1] = temp;
            }
            
            dict->len_d++;
            break;
        }
        if(i == dict->len_d) // if end of dictionary if reached than varible word is bigger than every word in dictionary
        {
            char *temp;
            
            if( !(dict->words[dict->len_d + 1] = (char*)malloc( (len_w + 1)*sizeof(char))) )
            {
                return -2;
            }
            
            strcpy(dict->words[dict->len_d + 1], word);
            
            // puts '\0' in dict.words[ dict.len_d ]
                        
            temp = dict->words[dict->len_d + 1];
            dict->words[dict->len_d + 1] = dict->words[dict->len_d];
            dict->words[dict->len_d] = temp;
            
            dict->len_d++;
            break; 
        }
        if(val == 0) // found same word in dictionary
        {
            return 0;
        }
    }
    return 1;
}


