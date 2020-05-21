char **sort_words_file(FILE *file , int *error); 
/* cheates array of strings (E.g  char **dictionary)
 * puts every word (in non emply file) as elemen of array (E.g dictionary[1] == {first word} ) 
 * end of array is string == "'\0'" (E.g dictionary[i][0] == 0 )
 * returns this array (char **dictionary)
 * return NULL pointer if error ! = 0
 * error = 2 if fscanf coud not read a symbol
 * error = 3 if malloc coud not allocate memory  
 * if file is empty than returns empty c string
*/


int str_put_in_dictionary(char ***dictionary,int len_d, char *word,int len_w);
