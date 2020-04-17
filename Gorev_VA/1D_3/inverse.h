typedef enum { OK = 0, MATR_IS_SINGULAR } ErrorCode;
#define eps 0.0000001

double Abs(double x);
double Abs(double x)
{
	if (x >= 0)
		return x;
	return -x;
}

double *centr_sym(double *matr, int n);
double *centr_sym(double *matr, int n)
{
	double *T;
	T = (double*)malloc(n * n * sizeof(double));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			T[i * n + j] = matr[(n - 1 - i) * n + (n - 1 - j)];
	return T;
}

double *swap(double *matr, int m, int n, int i1, int i2);
double *swap(double *matr, int m, int n, int i1, int i2)
{
	double *A;
	if (i1 == i2)
		return matr;
	if (i1 > i2)
	{
		A = (double*)malloc(sizeof(double));
		A[0] = i1;
		i1 = i2;
		i2 = A[0];
		free(A);
	}
	A = (double*)malloc(m * n * sizeof(double));

	for (int i = 0; i < i1; i++)
		for (int j = 0; j < n; j++)
			A[i * n + j] = matr[i * n + j];
	for (int j = 0; j < n; j++)
		A[i1 * n + j] = matr[i2 * n + j];
	for (int i = i1 + 1; i < i2; i++)
		for (int j = 0; j < n; j++)
			A[i * n + j] = matr[i * n + j];
	for (int j = 0; j < n; j++)
		A[i2 * n + j] = matr[i1 * n + j];
	for (int i = i2 + 1; i < m; i++)
		for (int j = 0; j < n; j++)
			A[i * n + j] = matr[i * n + j];

	return A;
}

double *multiply(double *matr, int m, int n, int i1, double c);
double *multiply(double *matr, int m, int n, int i1, double c)
{
	double *A;
	A = (double*)malloc(m * n * sizeof(double));
	for (int i = 0; i < i1; i++)
		for (int j = 0; j < n; j++)
			A[i * n + j] = matr[i * n + j];
	for (int j = 0; j < n; j++)
		A[i1 * n + j] = c * matr[i1 * n + j];
	for (int i = i1 + 1; i < m; i++)
		for (int j = 0; j < n; j++)
			A[i * n + j] = matr[i * n + j];
	return A;
}

double *plus_str(double *matr, int m, int n, int i1, int i2, double c);
double *plus_str(double *matr, int m, int n, int i1, int i2, double c)
{
	double *A;
	A = (double*)malloc(m * n * sizeof(double));
	for (int i = 0; i < i1; i++)
		for (int j = 0; j < n; j++)
			A[i * n + j] = matr[i * n + j];
	for (int j = 0; j < n; j++)
		A[i1 * n + j] = matr[i1 * n + j] + c * matr[i2 * n + j];
	for (int i = i1 + 1; i < m; i++)
		for (int j = 0; j < n; j++)
			A[i * n + j] = matr[i * n + j];
	return A;
}

void diag(double *A, double *A_dop, int n, int *Error);
void diag(double *A, double *A_dop, int n, int *Error)
{
	double *B, *B_dop;
	B = A, B_dop = A_dop;
	for (int k = 0; k < (n - 1); k++)
	{
		*Error = MATR_IS_SINGULAR;
		for (int i = k; i < n; i++)
		{
			if (Abs(A[i * n + k]) >= eps)
			{
				*Error = OK;
				A_dop = swap(A_dop, n, n, k, i);
				A = swap(A, n, n, k, i);

				A_dop = multiply(A_dop, n, n, k, 1.0 / A[k * n + k]);
				A = multiply(A, n, n, k, 1.0 / A[k * n + k]);
				break;
			}
		}
		if (*Error == OK)
		{
			for (int i = k + 1; i < n; i++)
				for (int j = k; j < n; j++)
				{
					A_dop = plus_str(A_dop, n, n, i, k, -A[i * n + k] / A[k * n + k]);
					A = plus_str(A, n, n, i, k, -A[i * n + k] / A[k * n + k]);
				}
		}
		else
			break;
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			B_dop[i * n + j] = A_dop[i * n + j];
			B[i * n + j] = A[i * n + j];
		}
}

double *inverse(double *A, int n, int *Error);
double *inverse(double *A, int n, int *Error)
{
	double *A_dop;
	A_dop = (double*)malloc(n * n * sizeof(double));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i == j)
				A_dop[i * n + j] = 1;
			else
				A_dop[i * n + j] = 0;

	diag(A, A_dop, n, Error);
	A = centr_sym(A, n);
	A_dop = centr_sym(A_dop, n);
	diag(A, A_dop, n, Error);
	return centr_sym(A_dop, n);
}