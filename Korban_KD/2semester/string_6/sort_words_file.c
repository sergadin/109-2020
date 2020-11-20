#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort_words_file.h"

#define NUM 1024



char **sort_words_file(FILE *file , int *error)
{
    char c;
    int len_b = 0, len_w = 0, len_d = 1;
    char buf[NUM + 1],  *word = NULL;
    char **dictionary;
    
    
    if( !(dictionary = (char**)malloc(1*sizeof(char*))) )
    {
        *error = 3;
        return NULL;
    }
    
    if( !(dictionary[0] = (char*)malloc(1*sizeof(char))) )
    {
        *error = 3;
        return NULL;
    }
    
    dictionary[0][0] = 0;
    
    buf[0] = 0;
    
    while(fscanf(file, "%c", &c) == 1)
    {
        if( (c != '\0') && (c != '\n') && (c != '\r') && (c != ' ') && (c != '	')) //reading word from file 
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
                if(len_b != 0)
                {
                    word = realloc(word, (len_w + NUM + 1)*sizeof(char));
                    strcpy(&word[len_w], buf);
                }
                len_w += len_b;
                
                for(int i = 0; i < len_d; i++)// putting word in dictionary
                {
                    int val = strcmp(dictionary[i], word);

                    if(val > 0) // find place whe to put word
                    {
                        dictionary = realloc(dictionary, (len_d + 1)*sizeof(char*) );
                        if( !(dictionary[len_d] = (char*)malloc( (len_w + 1)*sizeof(char))) )
                        {
                            *error = 3;
                            return NULL;
                        }
                        
                        strcpy(dictionary[len_d], word);

                        for(int j = len_d ; j > i; j--)// puts dictionary[len_d] i correc position
                        {
                            char *temp = dictionary[j];
                            dictionary[j] = dictionary[j - 1];
                            dictionary[j - 1] = temp;
                        }

                        len_d++;
                        break;
                    }
                    if(i == len_d - 1) // if end of dictionary if reached than varible word is bigger than every word in dictionary
                    {
                        char *temp;
                        dictionary = realloc(dictionary, (len_d + 1)*sizeof(char*) );
                        if( !(dictionary[len_d] = (char*)malloc( (len_w + 1)*sizeof(char))) )
                        {
                            *error = 3;
                            return NULL;
                        }
                        
                        strcpy(dictionary[len_d], word);
                        
                        // puts '\0' in last dictionary[i]
                        
                        temp = dictionary[len_d];
                        dictionary[len_d] = dictionary[len_d - 1];
                        dictionary[len_d - 1] = temp;
                        
                        len_d++;
                        break;
                    }
                    if(val == 0) // found same word in dictionary
                    {
                        break;
                    }
                }   
                len_w = 0;
                len_b = 0;
                
            }
        }
    }
    // file may end before word 
    if( (len_w > 0) || (len_b > 0) ) //
    {
        if(len_b != 0)
        {
            word = realloc(word, (len_w + NUM + 1)*sizeof(char));
            strcpy(&word[len_w], buf);
        }
                
        len_w += len_b;
                
        for(int i = 0; i < len_d; i++) 
        {
            int val = strcmp(dictionary[i], word);
            if(val > 0)
            {
                dictionary = realloc(dictionary, (len_d + 1)*sizeof(char*) );
                if( !(dictionary[len_d] = (char*)malloc( (len_w + 1)*sizeof(char))) )
                {
                    *error = 3;
                    return NULL;
                }
                        
                strcpy(dictionary[len_d], word);
                        
                for(int j = len_d ; j > i; j--)
                {
                    char *temp = dictionary[j];
                    dictionary[j] = dictionary[j - 1];
                    dictionary[j - 1] = temp;
                }
                break;
            }
            if(i == len_d - 1)
            {
                dictionary = realloc(dictionary, (len_d + 1)*sizeof(char*) );
                if( !(dictionary[len_d] = (char*)malloc( (len_w + 1)*sizeof(char))) )
                {
                    *error = 3;
                    return NULL;
                }
                        
                strcpy(dictionary[len_d], word);
                
                for(int j = len_d ; j > i; j--)
                {
                    char *temp = dictionary[j];
                    dictionary[j] = dictionary[j - 1];
                    dictionary[j - 1] = temp;
                }
                
                break;
            }
            if(val == 0)
            {
                break;
            }
        }
    }
    
    if(!feof(file))
    {
        *error = 2;
        return NULL;
    }
    error = 0;
    free(word);
    fclose(file);
    return dictionary;
    
}


