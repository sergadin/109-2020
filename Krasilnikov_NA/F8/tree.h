static int fn(const char *file, const struct stat *sb, int flag);
void make_tree(char *directory, FILE *fout);
void print_tree(char *directory, FILE *fout, char **FL, int cs, int depth);
int comp(const void *arg1, const void *arg2);
void count_tree(char *directory, char **FL, int depth);
