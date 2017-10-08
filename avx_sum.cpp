#include "avx_sum.h"

double avx_sum_calc(const double *in, arr_size num)
{
	double sum = 0;
	const size_t ITER_NUM = 8;
	size_t size_width = num / ITER_NUM;
	size_t size_re = num % ITER_NUM;
	__m256d input1;
	__m256d input2;
	__m256d output;
	for (size_t i = 0; i < size_width; ++i)
	{
		 input1 = _mm256_load_pd(in);
		 input2 = _mm256_load_pd(in + 4);
		 output = _mm256_add_pd(input1, input2);
		sum += output.m256d_f64[0] + output.m256d_f64[1]+output.m256d_f64[2] + output.m256d_f64[3];
		in += ITER_NUM;

	}
	for (size_t i = 0; i < size_re; ++i)
		sum += in[i];
	return sum;

}
