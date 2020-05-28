struct matr
{
	int e;
	int r;
	int c;
	char ***m;
};

int slength(const char *string);
char *scopy(const char *from, char *to);
char *sread(FILE *fin);
void matrix_transformation(FILE *fin, FILE *fout);
struct matr matrix_reading(FILE *fin);
void free_2D(struct matr matrix);
char sir (char** row, int cow, int number);
void printmatr(struct matr matrix, FILE *fout);
