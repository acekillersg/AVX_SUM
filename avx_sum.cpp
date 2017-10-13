#include "avx_sum.h"

double avx_sum_calc_d(const double *in, arr_size num)
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
		sum += output.m256d_f64[0] + output.m256d_f64[1] + output.m256d_f64[2] + output.m256d_f64[3];
		in += ITER_NUM;
	}
	for (size_t i = 0; i < size_re; ++i)
		sum += in[i];
	return sum;

}

float avx_sum_calc_s(const float *in, arr_size num)
{
	float sum = 0;
	const size_t ITER_NUM = 16;
	size_t size_width = num / ITER_NUM;
	size_t size_re = num % ITER_NUM;
	__m256 input1;
	__m256 input2;
	__m256 output;
	for (size_t i = 0; i < size_width; ++i)
	{
		input1 = _mm256_load_ps(in);
		input2 = _mm256_load_ps(in + 8);
		output = _mm256_add_ps(input1, input2);
		sum += output.m256_f32[0] + output.m256_f32[1] + output.m256_f32[2] + output.m256_f32[3] + output.m256_f32[4] + output.m256_f32[5] + output.m256_f32[6] + output.m256_f32[7];
		in += ITER_NUM;
	}
	for (size_t i = 0; i < size_re; ++i)
		sum += in[i];
	return sum;

}

/*
When this file is compiled by gcc, you will use the following codes
//////////////////////////////////////////////////////////////////

double avx_sum_calc(const double *in, arr_size num)
{
	double sum = 0;
	ATTR_ALIGN(32) double buf[4] = {};
	const size_t ITER_NUM = 8;
	size_t size_width = num / ITER_NUM;
	size_t size_re = num % ITER_NUM;

	for (size_t i = 0; i < size_width; ++i)
	{
		__m256d input1 = _mm256_load_pd(in);
		__m256d input2 = _mm256_load_pd(in + 4);
		__m256d output = _mm256_add_pd(input1, input2);
		_mm256_store_pd(buf, output);
		for (size_t i = 0; i<4; ++i)
			sum += buf[i];
		in += ITER_NUM;
	}
	for (size_t i = 0; i < size_re; ++i)
		sum += in[i];
	return sum;
}
/////////////////////////////////////////////
*/

