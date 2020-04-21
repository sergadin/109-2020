#define EL(m, n, i, j) \
	((m)[(n) * (i) + j])

void swap(double *data, int n, int row1, int row2);
void plus(double *data, int n, int row1, int row2, double s);
double dete(double *data, int n);

