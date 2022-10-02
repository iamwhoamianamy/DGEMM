#include <stdio.h>
#include <stdlib.h>

int flat_id(int i, int j, int height)
{
	return j * height + i;
}

void set_elem(int i, int j, double val, int height, double *M)
{
	M[flat_id(i, j, height)] = val;
}

double get_elem(int i, int j, int height, double *M)
{
	return M[flat_id(i, j, height)];
}

char size(int height, int width)
{
	return sizeof(double) * height * width;
}

void simple_mult(int M, int N, int K, double *A, double *B, double *C)
{

}

void blas_dgemm(int M, int N, int K, double *A, double *B, double *C)
{

}

int main(int argc, char **argv)
{
	size_t height = 3;
	size_t width = 3;
	size_t elem_count = height * width; 
	
	double *A = (double*)malloc(elem_count * sizeof(*A));
	double *B = (double*)malloc(elem_count * sizeof(*B));
	double *C = (double*)malloc(elem_count * sizeof(*C));

	for(size_t i = 0; i < height; i++)
	{
		for(size_t j = 0; j < width; j++)
		{
			double value = get_elem(i, j, height, A);
			printf("%lf ", value);
		}

		printf("\n");
	}

	printf("Hello, world!");
	return 0;
}