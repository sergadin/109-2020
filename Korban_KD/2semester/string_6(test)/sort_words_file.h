struct dictionary {
    char **words;
    int len_d; // number of words in dictionary
    int size; // size of char **words
};

enum RETURN_CODES
{
    INPUT_ERROR = -3,
    MEMORY_ERROR,
    READ_ERROR,
};


struct dictionary sort_words_file(FILE *file , int *error); 
/* creates struct dictionary
 * puts every word (in non emply file) as elemen of char **words (E.g dictionary.words[1] == {first word} ) 
 * returns dictionary 
 * if function encouted an error  int *error !=0
 * int *error == INPUT_ERROR if file is empty
 * int *error == READ_ERROR if fscanf coud not read a symbol
 * int *error == MEMORY_ERROR if malloc coud not allocate memory
 * if error != 0 dictionary will contain succesfully read words (may contain garbage)
 */


int str_put_in_dictionary(struct dictionary *dict, char *word, int len_w);
/* puts word in   sorted!   dictionary with allocation of memory
 * returns 1 if succesfully put word in dictionary
 * returns 0 if word is already in dictionary
 * returns -1 if malloc coud not allocate memory 
*/
