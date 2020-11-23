struct dictionary {
    char **fpaths;
    long int *f_sizes; //size of files
    int len_d; // number of words in dictionary
    int size; // size of char **words
}; 

struct dictionary sort_files_by_size(const char *dir_name, int *error);
/* creates struct dictionary
 * note! dictionary must be freed afted use
 * puts filepaths of files in char **fpaths
 * puts sizes of files in int *F_size
 * automaticly extends dictionary
 * 
 * returns dictionary
 * if error !=0 function encounted an error
 * error == -1 if dir_name is incorrect
 * error == -2 if malloc coud not allocate memory
 * if error != 0 dictionary will contain succesfully 'read' fiels (may contain garbage)
 */
