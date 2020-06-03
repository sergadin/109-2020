//на ц зачет
//В текстовом файле записана матрица действительных чисел. Формат данных: два натуральных числа n и m, задающих соответственно число строк и столбцов матрицы, и последовательность действительных чисел, соответствующая записи матрицы по строкам. Требуется найти строчку матрицы, удовлетворяющую заданному условию (если таких несколько, то выбираем строку с минимальным номером), выполнить указанное преобразовании матрицы, и напечатать получившуюся матрицу с сохранением формата в
#include<stdio.h>
#include<math.h>

#include"52.h"


int main (void) {
	int error = -1;
	int N, M;
	FILE * input , * output ;
	

	if (( input = fopen("input.txt" , "r")) == NULL ) {
		printf ("Не удалось открыть файл") ;
		return -1;
	}
	if (( output = fopen("output.txt" , "w")) == NULL ) {
    		printf ("Не удалось открыть файл") ;
        	fclose(input);
		return -1;
	}  
	if(fscanf(input, "%d", &N) != 1 || N <= 0) {
		printf("невозможно прочитать количесвто строк\n");
		fprintf(output,"%d\n error read N",error);
		fclose(input);
		fclose(output);
		return 0;
	}		
	if(fscanf(input, "%d", &M) != 1 || M <= 0){
		fprintf(output,"%d\n error read M",error);
		printf("невозможно прочитать количесвто столбцов\n");
		fclose(input);
		fclose(output);
		return 0;
	}
   
//	printf("%d\n", N);
//	printf("%d\n", M);

    double *matrix = malloc(sizeof(double *) * (N * M)); 
   
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
	    	if (fscanf(input, "%lf", &matrix[i * M + j]) != 1) {
	        	printf("недостаточно элементов\n");
			fprintf(output,"%d\n please add more elements",error);
	        	free(matrix);
	        	fclose(input);
			fclose(output);
	        	return 0;
	    	}
		}
    }
	solve(output, N, M, matrix) ;
//	print_matrix(output, n, m, matrix);
	fclose(output);

free(matrix);
fclose(input);
return 0;
}

