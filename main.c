#include <stdio.h>

inline int flat_id(int i, int j, int height)
{
	return j * height + i;
}

inline void set_value(int i, int j, double val, int height, double *M)
{
	M[flat_id(i, j, height)] = val;
}

inline void get_value(int i, int j, int height, double *M)
{
	return M[flat_id(i, j, height)];
}

inline char size(int height, int width)
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
	
	double *A = kmalloc_array(elem_count, sizeof(*A), GFP_KERNEL);
	double *B = kmalloc_array(elem_count, sizeof(*B), GFP_KERNEL);
	double *C = kmalloc_array(elem_count, sizeof(*C), GFP_KERNEL);

	printf("Hello, world!");
	return 0;
}