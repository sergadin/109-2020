typedef enum {MATRIX_OK = 0, INCORRECT_INPUT_FORMAT ,INCORRECT_SIZE, ALLOCATION_ERROR} ErrorCode;

void matrix_transformation(FILE *fin, FILE *fout, ErrorCode *ma);
int matrix_reading(FILE *fin, char ***matrix, int rows, int columns);
int slength(const char *string);
char *scopy(const char *from, char *to);



char *sread(FILE *fin);
