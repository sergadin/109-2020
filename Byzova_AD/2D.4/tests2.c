#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include"2.h"

int main(void) {

	int error = -1;
	double **matrix;
	int N, M;
	FILE *input , *output ;
	int k, j, i;
	double current;

	if (( input = fopen("input.txt" , "r")) == NULL ) {
		printf ("Не удалось открыть файл") ;
		return -1;
	}
	if (( output = fopen("output.txt" , "w")) == NULL ) {
    	printf ("Не удалось открыть файл\n") ;
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
	matrix = (double**)malloc(N * sizeof(double*));
	
	for(k = 0; k < N; k++)
		matrix[k] = (double *)malloc(M *sizeof(double));

	for (i = 0; i < N; i++) {

        for (j = 0; j < M; j++) {

            if (fscanf(input, "%lf", &current) != 1) {
                printf("please add more elements\n");
				fprintf(output,"%d\n error read elements",error);
                for(k = 0; k < N; k++) {
  //              	if(matrix[k])
                    	free(matrix[k]);
                }
  //              free(matrix);
                fclose(input);
				fclose(output);
                return -1;
            }
			matrix[i][j] = current;
        }
    }
	answers(N, M, matrix, output);
	fclose(output);	

	for (k = 0; k < N; k++) {
//		if(matrix[k])
			free(matrix[k]);
	}

//	free(matrix);
	fclose(input);
	return 0;
}
