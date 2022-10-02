#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <math.h>

int flat_id(int i, int j, int height)
{
	return j * height + i;
}

double get_elem(int i, int j, int height, double *M)
{
	return M[flat_id(i, j, height)];
}

void set_elem(int i, int j, int height, double *M, double val)
{
	M[flat_id(i, j, height)] = val;
}

char size(int height, int width)
{
	return sizeof(double) * height * width;
}

void simple_mult(int M, int N, int K, double *A, double *B, double *C)
{
        double sum = 0;
        size_t i, j, k;

	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
			sum = 0;

			for (k = 0; k < K; k++) {
				sum += get_elem(i, k, M, A) * get_elem(k, j, K, B);
			}	

			set_elem(i, j, M, C, sum);
		}	
	}
}

int num_of_threads = 2;

void blas_dgemm(int M, int N, int K, double *A, double *B, double *C)
{
        size_t i, j, k;

        #pragma omp parallel shared(A, B, C) private(i, j, k) num_threads(num_of_threads)
        {
                double sum = 0;

                #pragma omp for schedule(static)
                for (i = 0; i < M; i++) {
                        for (j = 0; j < N; j++) {
                                sum = 0;

                                for (k = 0; k < K; k++) {
                                        sum += get_elem(i, k, M, A) * get_elem(k, j, K, B);
                                }	

                                set_elem(i, j, M, C, sum);
                        }	
                }
        }
}

void printMatrix(int height, int width, double *M)
{
	for(size_t i = 0; i < height; i++) {
		for(size_t j = 0; j < width; j++) {
			printf("%lf ", get_elem(i, j, height, M));
		}

		printf("\n");
	}
}

void init_matrix_incr(int height, int width, double *M)
{
	int k = 1;
	for(size_t i = 0; i < height; i++) {
		for(size_t j = 0; j < width; j++) {
			set_elem(i, j, height, M, k);
			k++;
		}
	}
}

void init_matrix_rand(int height, int width, double *M)
{
	for(size_t i = 0; i < height; i++)
		for(size_t j = 0; j < width; j++)
			set_elem(i, j, height, M, (double)rand() / RAND_MAX);
}

void init_matrix_val(int height, int width, double *M, double val)
{
	for (size_t i = 0; i < height * width; i++)
		M[i] = val;	
}

double sum_of_elems(int height, int width, double* M)
{
        double sum = 0;

        for (size_t i = 0; i < height * width; i++)
                sum += M[i];        

        return sum;
}

int main(int argc, char **argv)
{
	if(argc != 5)
	{
		printf("Enter arguments: \n");
                printf("\t%s ", argv[0]);
                printf("M ");
                printf("N ");
                printf("K ");
                printf("number_of_threads");
		return 1;
	}

	size_t M = atoll(argv[1]);
	size_t K = atoll(argv[2]);
	size_t N = atoll(argv[3]);

	double *A = (double*)malloc(M * K * sizeof(*A));
	double *B = (double*)malloc(K * N * sizeof(*B));
	double *C = (double*)malloc(M * N * sizeof(*C));

	init_matrix_rand(M, K, A);
	init_matrix_rand(K, N, B);
	init_matrix_val(M, N, C, 0.0);

	double simple_start = omp_get_wtime();
        simple_mult(M, N, K, A, B, C);
        double simple_time = omp_get_wtime() - simple_start;
	printf("Simple mult time: %lf, ", simple_time);
        printf("sum = %lf\n", sum_of_elems(M, N, C));

        num_of_threads = atoll(argv[4]);
        
	double dgemm_start = omp_get_wtime();
        blas_dgemm(M, N, K, A, B, C);
        double dgemm_time = omp_get_wtime() - dgemm_start;
	printf("DGEMM mult time:  %lf, ", dgemm_time);
        printf("sum = %lf\n", sum_of_elems(M, N, C));

        printf("Speedup: %lf\n", simple_time / dgemm_time);

        free(A);
        free(B);
        free(C);

        return 0;
}