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
                printf("%d\n", len_b);
                
                if(len_b != 0)
                {
                    word = realloc(word, (len_w + strlen(buf) + 1)*sizeof(char));
                    strcpy(&word[len_w], buf);
                    buf[0] = 0;
                }
                
                len_w += len_b;
                printf("%s\n", dictionary[0]);
                temp = str_put_in_dictionary(dictionary, len_d, word, len_w);
                if(!temp)
                {
                    *error = 3;
                    return NULL;
                }
                if(temp == 1)
                    len_d++;
                len_w = 0;
                len_b = 0;
                word = NULL;
                
            }
        }
    }
    
    // file may end before word 
    if( (len_w > 0) || (len_b > 0) ) //
    {
        int temp;
        if(len_b != 0)
        {
            word = realloc(word, (len_w + NUM + 1)*sizeof(char));
            strcpy(&word[len_w], buf);
        }
                
        len_w += len_b;
                
        temp = str_put_in_dictionary(dictionary, len_d, word, len_w);
        if(!temp)
        {
            *error = 3;
            return NULL;
        }
        if(temp == 1)
            len_d++;
    }
    
    if(!feof(file))
    {
        *error = 2;
        return NULL;
    }
    printf("ok\n");
    error = 0;
    free(word);
    fclose(file);
    return dictionary;
    
}




int str_put_in_dictionary(char **dictionary,int len_d, char *word, int len_w)
{
    for(int i = 0; i < len_d; i++)// putting word in dictionary
    {
        int val = strcmp(dictionary[i], word);
        if(val > 0) // find place where to put word
        {
            dictionary = realloc(dictionary, (len_d + 1)*sizeof(char*) );
                        
            if( !(dictionary[len_d] = (char*)malloc( (len_w + 1)*sizeof(char))) )
            {
                return -1;
            }
            
            strcpy(dictionary[len_d], word);

            for(int j = len_d ; j > i; j--)// puts dictionary[len_d] in correct position
            {
                char *temp = dictionary[j];
                dictionary[j] = dictionary[j - 1];
                dictionary[j - 1] = temp;
            }
            break;
        }
        if(i == len_d - 1) // if end of dictionary if reached than varible word is bigger than every word in dictionary
        {
            char *temp;
            
            printf("ok2\n");
            dictionary = realloc(dictionary, (len_d + 1)*sizeof(char*) );
            
            if( !(dictionary[len_d] = (char*)malloc( (len_w + 1)*sizeof(char))) )
            {
                return -1;
            }
                        
            strcpy(dictionary[len_d], word);
            
            // puts '\0' in last dictionary[i]
                        
            temp = dictionary[len_d];
            dictionary[len_d] = dictionary[len_d - 1];
            dictionary[len_d - 1] = temp;
            
            printf("%s\n",dictionary[0]);
            break; 
        }
        if(val == 0) // found same word in dictionary
        {
            return 0;
        }
    }
    return 1;
}


