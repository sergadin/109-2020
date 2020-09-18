#define EL(m, n_cols, row, col) \
	((m)[(n_cols) * (row) + col])

int find_row(double *data, int n_rows, int n_cols);//Функция, чтобы находить максимальный элемент матрицы

void printmat(double *data, int n_rows, int n_cols,int t);//Функция чтобы печатать матрицу
void sort(double *data, int n_rows, int n_cols, int t);


