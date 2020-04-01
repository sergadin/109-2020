typedef enum {
	OK,
	NOT_DETERMINED,
	CANNOT_ALLOCATE_MEMORY
} Status;

double *solve_system(double **matrix, int n, double precision, Status *s);
void clear_two_dimensional_matrix(double **matrix, int n);
