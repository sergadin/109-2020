#include <stdio.h>
#include "rank.h"
#include <math.h>

double mrank(double **matrix2d, int n_row, int n_col, double eps) {
    int rank = 0, ind = 0, i, j;
    double s;
    while(!((rank == n_row - 1) || (i == n_col - 1))) {
        for(i = 0; i < n_col; i++) {
			ind = 0;
			for(j = rank; j < n_row; j++) {
				if(!(fabs(matrix2d[i][j]) < eps))	{
					ind = 1;
					break;
				}
			}
			if(ind == 1)
				break;
		}
		if(ind == 0) {
			rank -= 1;
			break;
		}
		if(fabs(matrix2d[rank][i]) < eps) {
            for (int r = 0; r < n_col; r++) {
                s = matrix2d[i][r];
                matrix2d[i][r] = matrix2d[j][r];
                matrix2d[rank][r] = s;
            }
        }
		for(j = rank + 1; j < n_row; j++) {
			if(!(fabs(matrix2d[j][i]) < eps)) {
                s = (-1) * matrix2d[j][i] / matrix2d[rank][i];
                for(i = 0; i < n_col; i++)
                    matrix2d[j][i] += s * matrix2d[rank][i];
			}
		}
		rank++;
	}
    rank++;
	return rank;
}
