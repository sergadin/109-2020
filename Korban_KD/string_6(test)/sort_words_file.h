
struct dictionary {
    char **words;
    int len_d; // number of words in dictionary
    int size; // size of char **words
};


struct dictionary sort_words_file(FILE *file , int *error); 
/* cheates array of strings (E.g  char **dictionary)
 * puts every word (in non emply file) as elemen of array (E.g dictionary[1] == {first word} ) 
 * end of array is string == "'\0'" (E.g dictionary[i][0] == 0 )
 * returns this array (char **dictionary)
 * return NULL pointer if error ! = 0
 * error = 2 if fscanf coud not read a symbol
 * error = 3 if malloc coud not allocate memory  
 * if file is empty than returns empty c string
*/


int str_put_in_dictionary(struct dictionary *dict, char *word, int len_w);
/* pust *word in dict
 *(dict.len_d + 1) should be  < (dict.size)
 *this function allocates memory for word in dict.words[ dict.len_d + 1]
*/
