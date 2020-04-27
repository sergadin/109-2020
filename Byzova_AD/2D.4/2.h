#include<stdio.h>
#include<stdlib.h>
#include<math.h>

	void str_diff(int i, int j, int m , int n,  double **matrix);
	void print_matrix(int n, int m, double **matrix);
	void str_change(int i,int j, int place, int m, double **matrix) ;
	void gauss_down(int n, int m, double **matrix) ; // ступенчатый вид
	void gauss_up(int n, int m,double **matrix) ;
	void answers(int n, int m, double **matrix, FILE *output);
