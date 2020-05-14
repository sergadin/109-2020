//решить систему линейных уравнений
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include"2.h"
#define EPS 0.0001

	void str_diff(int i, int j, int m , int n,  double **matrix){
		//подаем i,j элемент с которого строки надо вычитать с подх коэф
		int i0 = 0;
		int j0 = 0;
		double k = 1;
		for(i0 = n - 1 ; i0 > i; i0--) { // меняем строку и идем с конца вверх
			k = matrix[i0][j] / matrix[i][j]; // коэф для убийства нужного элемента строки
	//		printf("k (%lf) = %lf / %lf\n",k , matrix[i0][j], matrix[i][j]);
			for(j0 = 0; j0 < m; j0++){ //меняем столбец
				matrix[i0][j0] -= k * matrix[i][j0]; //вычитаем
			}
		}
	}
	
	void print_matrix(int n, int m, double **matrix){
    	printf("\nтеперь матрица\n");
		for(int i = 0; i < n; i++) {
        	for(int j = 0; j < m; j++) {
            	printf("%lf\t", matrix[i][j]);
        	}
    	printf("\n");
    	}
	}

	void str_change(int i,int place,double **matrix) {
	//i j это крайний элемент лесенки который надо поставить на место place,place  
		// t = a a = b b = t
		double *tmp = matrix[i];
	  	matrix[i] = matrix[place];
		matrix[place] = tmp;
	}
	
	void right_position(int c,int n, int m, double **matrix){
		print_matrix(n, m, matrix);	
		for(int i = c; i < n - 1; i++) {
			for(int k = i + 1; k < n; k++)
				if( fabs(matrix[i][c]) < fabs(matrix[k][c])) {
					str_change(i, k, matrix);//меняем
				}
		}
		print_matrix(n, m, matrix);	
	}

	void gauss_down(int n, int m, double **matrix) { // ступенчатый вид
		int i = 0;
		int without_repeat = 0;
		int c = 0; // счетчик угловых клеток
	    int j;	
		//находим первый ненулевой столбец i - номер строчки j - номер столбца
		for(j = 0; j < m - 1; j++){ // фиксируем столбец (последний не рассматриваем)
			right_position(c, n, m, matrix);
			for(i = without_repeat; i < n; i++){ // смотрим на разные строчки
				if ( fabs(matrix[i][j]) > EPS ) { 
				//нашли первый ненулевой элемент в столбце
		// теперь вычитаем остальные строки из той которую нашли с нужным коэф
//					printf("\ni =%d j = %d\n", i, j);
					str_change(i,c,matrix);//ставим строку на нужное место
					str_diff(c, c, m, n, matrix); //вычитаем остальные
//					print_matrix(n, m, matrix);
					without_repeat = c + 1; //все ступеньки до с строки сделаны
					break;
				}
			}
			c++;
		}
		print_matrix(n, m, matrix);	
	}
	
	void gauss_up(int n, int m,double **matrix) {
		double koef = 1;
		for(int c = n - 1; c > 0; c--) {//c,c - угловые элементы
			if( fabs(matrix[c][c]) > EPS ) {
//			printf("m[c][c] = %lf\n\n", matrix[c][c]);
				for(int i = c - 1; i >= 0; i-- ) {
					if(fabs(matrix[i][c]) > EPS) {
//			printf("m[i][c] = %lf\n", matrix[i][c]);
						koef = matrix[i][c] / matrix[c][c];
//			printf("k (%lf) = %lf / %lf\n",koef , matrix[i][c], matrix[c][c]);
						for(int j = 0; j < n; j++) {
							matrix[i][j] -= koef * matrix[c][j];
						}
					}
				}
			}
		}
		print_matrix(n, m, matrix);	
	}

void answers(int n, int m, double **matrix, FILE *output) {
	int error = -2;
	double x_i;
	int i;
	gauss_down(n, m, matrix) ;
	gauss_up(n, m, matrix);
	for (i = 0; i < n; i++){
		if (fabs(matrix[i][i]) > EPS) {
			x_i = matrix[i][m - 1] / matrix[i][i];
			printf("x_%d = %lf\n", i, x_i);
			fprintf(output, "x_i = %lf\n", x_i);
		}
		else {
			printf("\n%d несовместная система или бесконечно много решений\n", error);
			fprintf(output,"error %d\t несовместная система или бесконечно много решений", error);	
		break;	
		}
	}
}



