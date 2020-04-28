int invert_matrix (int n, double * a, double *b);
/*
 * finds inverted matrix for a and puts in in b
 */
double find_max_abs_redused(int n, double *a, int start,int *max_i,int *max_j);

enum INVERT_MATRIX
{
    DETERMINANT_0 = 0,
    OK,
};
 
