#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

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
	for (size_t i = 0; i < M; i++) {
		for (size_t j = 0; j < N; j++) {
			double sum = 0;

			for (size_t k = 0; k < K; k++) {
				sum += get_elem(i, k, M, A) * get_elem(k, j, K, B);
			}	

			set_elem(i, j, M, C, sum);
		}	
	}
}

void blas_dgemm(int M, int N, int K, double *A, double *B, double *C)
{
	for (size_t i = 0; i < M; i++) {
                for (size_t j = 0; j < N; j++) {
                        double sum = 0;

                        for (size_t k = 0; k < K; k++) {
                                sum += get_elem(i, k, M, A) * get_elem(k, j, K, B);
                        }	

                        set_elem(i, j, M, C, sum);
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

int main(int argc, char **argv)
{
	if(argc != 5)
	{
		printf("Enter arguments: \n");
                printf("\tM\n");
                printf("\tN\n");
                printf("\tK\n");
                printf("\talg: [simple|dgemm]\n");
		return 1;
	}

	size_t M = atoll(argv[1]);
	size_t K = atoll(argv[2]);
	size_t N = atoll(argv[3]);

        enum algorithm
        {
                simple = 0,
                dgemm = 1
        };

        int alg;

        if(strcmp(argv[4], "simple") == 0) {
                alg = simple;
        } else if(strcmp(argv[4], "dgemm") == 0) {
                alg = dgemm;
        } else {
                printf("Unknown algorithm!");
                return 1;
        }
        
		
	double *A = (double*)malloc(M * K * sizeof(*A));
	double *B = (double*)malloc(K * N * sizeof(*B));
	double *C = (double*)malloc(M * N * sizeof(*C));

	init_matrix_rand(M, K, A);
	init_matrix_rand(K, N, B);
	init_matrix_val(M, N, C, 0.0);

	double start = omp_get_wtime();
        
        switch (alg) {
        case simple:
	        simple_mult(M, N, K, A, B, C);
                break;
        case dgemm:
                blas_dgemm(M, N, K, A, B, C);
                break;
        }

	double time = omp_get_wtime() - start;

	printf("Simple mult time: %lf", time);

	printf("\n");
	return 0;
}