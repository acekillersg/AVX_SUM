
#ifndef AVX_SUM_H
#define AVX_SUM_H
#include <iostream>
#include <intrin.h>

using arr_size = unsigned int;

double avx_sum_calc_d(const double *in, arr_size num);
float avx_sum_calc_s(const float *in, arr_size num);


#endif

