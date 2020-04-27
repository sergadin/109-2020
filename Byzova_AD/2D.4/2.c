//решить систему линейных уравнений
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include"2.h"


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

	void str_change(int i, int j, int place, int m, double **matrix) {
	//i j это крайний элемент лесенки который надо поставить на место place,place  
		// t = a a = b b = t
		int j0;
		double tmp;
		for(j0 = j; j0 < m; j0++) { 
			tmp = matrix[i][j0];
			matrix[i][j0] = matrix[place][j0];
			matrix[place][j0] = tmp;
		}
	}

	void gauss_down(int n, int m, double **matrix) { // ступенчатый вид
		int i = 0;
		int i0 = 0;
		int c = 0; // счетчик угловых клеток
	    int j;	
		//находим первый ненулевой столбец i - номер строчки j - номер столбца
		for(j = 0; j < m - 1; j++){ // фиксируем столбец (последний не рассматриваем)
			for(i = i0; i < n; i++){ // смотрим на разные строчки
				if ( matrix[i][j] != 0 ) { 
				//нашли первый ненулевой элемент в столбце
		// теперь вычитаем остальные строки из той которую нашли с нужным коэф
//					printf("\ni =%d j = %d\n", i, j);
					str_diff(i, j, m, n, matrix);
//					print_matrix(n, m, matrix);
					str_change(i, j, c, m, matrix);
					i0 = i + 1;
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
			if( matrix[c][c] != 0 ) {
//			printf("m[c][c] = %lf\n\n", matrix[c][c]);
				for(int i = c - 1; i >= 0; i-- ) {
					if(matrix[i][c] != 0) {
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
	gauss_down(n, m, matrix) ;
	gauss_up(n, m, matrix);
	double x_i;
	for (int i = 0; i < n; i++){
		if (matrix[i][i] != 0) {
			x_i = matrix[i][m - 1] / matrix[i][i];
			printf("x_%d = %lf\n", i, x_i);
			fprintf(output, "%lf\n", x_i);
		}
		else {
			printf("несовместная система или бесконечно много решений");
			fprintf(output,"%d\t несовместная система или бесконечно много решений", error);	
		break;	
		}
	}
}



