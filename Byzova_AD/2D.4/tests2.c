#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include"2.h"

int main(void) {

	int error = -1;
	double **matrix;
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
		printf("невозможно прочитать количество строк\n");
		fprintf(output,"%d\n error read N",error);
		fclose(input);
		fclose(output);
		return 0;
	}		
	if(fscanf(input, "%d", &M) != 1 || M <= 0){
		fprintf(output,"%d\n error read M",error);
		printf("невозможно прочитать количество столбцов\n");
		fclose(input);
		fclose(output);
		return 0;
	}
	
	matrix = (double**)malloc(M * sizeof(double*));
	
	for( int k = 0; k < M; k++) {
		matrix[k] = (double *)malloc(N *sizeof(double));
	}

	for (int i = 0; i < N; i++) {

        for (int j = 0; j < M; j++) {

            if (fscanf(input, "%lf", &matrix[i][j]) != 1) {
                printf("please add more elements\n");
				fprintf(output,"%d\n error read elements",error);
                for(int k = 0; k < N; k++) {
                    free(matrix[k]);
                }
               // free(matrix);
                fclose(input);
				fclose(output);
                return -1;
            }
        }
    }
answers(N, M, matrix, output);
fclose(output);	
fclose(input);

for (int k = 0; k < N; k++) {
	free(matrix[k]);
}

//free(matrix);
return 0;
}

