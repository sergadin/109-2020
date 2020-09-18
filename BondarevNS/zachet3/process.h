typedef enum {MATRIX_OK = 0, DATAERR} ErrorCode;

void read_matrix(double *matrix, int n, int m, FILE *fin, ErrorCode *materr);
void founding_and_transformation(double *matrix, int n, int m);
void print_matrix(double *matrix, int n, int m, FILE *fout);
