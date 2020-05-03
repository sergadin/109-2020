// Определить ранг вещественной N × M матрицы.
#include<stdio.h>
#include<math.h>

#include"1.h"
#define CHECK_NOT_NULL 1
#define CHECK_NULL 0

	void str_diff(int i, int j, int m , int n,  double *matrix){
		//подаем i,j элемент с которого строки надо вычитать с подх коэф
		int i0 = 0;
		int j0 = 0;
		double k = 1;
		for(i0 = n - 1 ; i0 > i; i0--) { // меняем строку и идем с конца вверх
			k = matrix[i0 * m + j] / matrix[i * m + j]; // коэф для убийства нужного элемента строки
	//		printf("k (%lf) = %lf / %lf\n",k , matrix[i0 * m + j], matrix[i * m + j]);
			for(j0 = 0; j0 < m; j0++){ //меняем столбец
				matrix[i0 * m + j0] -= k * matrix[i * m + j0]; //вычитаем
			}
		}
	}
	
	void print_matrix(int n, int m, double *matrix){
    printf("\nтеперь матрица\n");
	for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            printf("%lf\t", matrix[i * m + j]);
        }
    printf("\n");
    }
}

	void algorithm(int n, int m, double *matrix) { // ступенчатый вид
	
		int i = 0;
		int without_repeat = 0;
	    int j;	
		//находим первый ненулевой столбец i - номер строчки j - номер столбца
		for(j = 0; j < m; j++){ // фиксируем столбец
			for(i = without_repeat; i < n - 1; i++){ // смотрим на разные строчки
			// мы идем по каждому из столбцов вниз и смотрим на элементы
				if ( matrix[i * m + j] > 0 || matrix[i * m + j] < 0 ) { 
			//нашли первый ненулевой элемент в столбце (i-ая строка) 
			// теперь вычитаем остальные строки из той которую нашли с нужным коэф
//					printf("\ni =%d j = %d\n", i, j);
					str_diff(i, j, m, n, matrix);
					print_matrix(n, m, matrix);
		//когда мы обнулили остальные строчки в котогрых элемент в j столбце
		//не нулевой, то мы должны перейти на следующую строку
		//чтобы у нас получился при выравнивании вид лесенки
		//так как я нахожу ранг выравнивать мне не нужно, достаточно
		//только понять сколько нулевых строк
					without_repeat = i + 1; 			
					break;
				}
			}
		}
	}	
	int check_null(int i, int n, int m, double *matrix){
		int i0 = i;
		int check = 1;
		for(int j = 0; j < m; j++){
//			printf("\nmatrix[%d*%d+%d] = %lf\n", i0, m, j, matrix[i0 * m + j]);
			if(matrix[i0 * m + j] > 0 || matrix[i0 * m + j] < 0) {
				check = 1;
				break;
			}
		}
		if(check > 0) return CHECK_NOT_NULL;
		else return CHECK_NULL;
	}
	int rk(int n, int m, double *matrix) {
//		int i = 0;
//		int j = 0;
		int res = 0;
		algorithm(n, m, matrix); // выравниваем матрицу до ступенчатого вида 
			for(int i = 0; i < n ; i++){ // проходимся по строкам
				res += check_null(i, n, m,matrix);
//				printf("\nres += %d\n",check_null(i,n,m,matrix) + 2);
			}
		return res;
	}








