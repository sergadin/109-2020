
void a_read(FILE *inp, char ***a);
int a_look(FILE *inp, char ***a, int n, int m);
int slen(const char *str);
char *cop(const char *f, char *t);
char *str_r(FILE *inp);

char *pol (char *str);
int eq (char *a, char *b);
enum RETURN_CODES
{
    SUCCESS,
    ERROR_READ,
    ERROR_OPEN,
};