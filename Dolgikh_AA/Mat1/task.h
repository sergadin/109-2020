#define EL(m, n_clos, row, col) \
	((m)[(n_cols) * (row) + col])
#define eps 0.000001

int rank(double *data, int n_rows, int n_cols);//Функция чтобы находить ранг матрицы
void swaprows(double *data, int n_cols, int row1, int row2);//Функция чтобы менять строчки местами
void swapcols(double *data, int n_rows, int n_cols, int col1, int col2);//Функция чтобы менять столбцы местами
void plusrows(double *data, int n_cols, int row1, int row2, double k);//Функция чтобы прибавлять к строчке строчку, умноженную на число
void printmat(double *data, int n_rows, int n_cols);//Функция чтобы печатать матрицу
