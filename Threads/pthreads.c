#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count; // Qtd de trheads
int m; // Linhas de A
int n; // Elementos em  m

float **A;
float *x;
float *y;

void Fill_Matriz(float *A[], int rows, int cols);
void Fill_Vector(float x[], int rows);
void Print_Vector(float x[], int rows);

// 
void *Pth_mat_vect(void *rank){
	long my_rank = (long) rank;
	int i, j;
	int local_m = m/thread_count;
	int my_first_row = my_rank*local_m;
	int my_last_row = (my_rank+1)*local_m -1;

	for (i = my_first_row; i <= my_last_row; i++){
		y[i] = 0.0;
		for (j = 0; j < n; j++)
			y[i] += A[i][j]*x[j];
	}
	return NULL;
}


int main(int argc, char* argv[]){
	if(argc != 4){
		printf("Inserir:  m n thread_count como argumentos\n");
		return EXIT_FAILURE;
	} else{
		m = atoi(argv[1]);
		n = atoi(argv[2]);
		thread_count = atoi(argv[3]);
	}

	pthread_t* threads = (pthread_t*) malloc(thread_count * sizeof(pthread_t));

	A = malloc(m* sizeof(float*));
	for(int i=0; i<m; i++)
		A[i] = malloc(n* sizeof(float));

	x = (float*) malloc(n* sizeof(float));
	y = (float*) malloc(m* sizeof(float));
	
	Fill_Matriz(A, m, n);
	Fill_Vector(x, m);

	for(int t=0; t < thread_count; t++)
		pthread_create(&threads[t], NULL, Pth_mat_vect, &t);
	
	for(int t=0; t < thread_count; t++)
		pthread_join(threads[t], NULL);

	printf("Tamanho: %d x %d e %d threads\n", m, n, thread_count);

	printf("Resposta:\n");
	Print_Vector(y, m);

	free(A);
	free(x);
	free(y);
	free(threads);
	
	return 0;
}


void Fill_Matriz(float *A[], int rows, int cols){
	int i, j;
	for (i = 0; i < rows; i++)
    		for (j = 0; j < cols; j++)
    			A[i][j] = rand() % 100;
}


void Fill_Vector(float x[], int rows){
	int i;
	for (i = 0; i < rows; i++)
		x[i] = rand() % 100;
}


void Print_Vector(float x[], int rows) {
   int   i;

   for (i = 0; i < rows; i++)
      printf("%.5f ", x[i]*1000);
   printf("\n");
}

