#define EL(m, n, i, j) \
	((m)[(n) * (i) + j])

char *readstring(FILE *input);
int find(char **matrix, int n, int m);
