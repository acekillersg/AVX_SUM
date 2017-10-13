#include "avx_sum.h"
#include <string>
#include <random>
#include <windows.h>

#ifndef ATTR_ALIGN
#  if defined(__GNUC__)    // GCC
#    define ATTR_ALIGN(n)    __attribute__((aligned(n)))
#  else    
#    define ATTR_ALIGN(n)    __declspec(align(n))
#  endif
#endif    // #ifndef ATTR_ALIGN

using namespace std;
//Timer class to calculate the excuting time
class MyTimer {
public:
	MyTimer() {}

	void TimerStart() {
		QueryPerformanceFrequency(&large_integer);
		DobDff = large_integer.QuadPart;

		QueryPerformanceCounter(&large_integer);
		IntStart = large_integer.QuadPart;
	}

	double TimerFinish() {
		QueryPerformanceCounter(&large_integer);
		IntEnd = large_integer.QuadPart;
		DobMillseconds = (IntEnd - IntStart) * 1000 / DobDff;
		return DobMillseconds;
	}
private:
	LARGE_INTEGER large_integer;
	__int64 IntStart;
	__int64 IntEnd;
	double DobDff;
	double DobMillseconds;

};

int main(int argc, char **argv)
{
	const arr_size NUM = 10000;
	MyTimer timer;
	ATTR_ALIGN(32) double ran_arr[NUM] = {};
	ATTR_ALIGN(32) float ran_arr_float[2 * NUM] = {};

	random_device de;
	mt19937 ran(de());     //generate the random number

	uniform_real_distribution<double> u_r_d(0.0, 10);

	double sum2 = 0;

	for (size_t i = 0; i < 2 * NUM; ++i)
	{
		double tmp = u_r_d(ran);
		if (i<NUM)
			ran_arr[i] = tmp;
		ran_arr_float[i] = tmp;
	}
	timer.TimerStart();
	for (size_t i = 0; i < NUM; ++i)
	{
		sum2 += ran_arr[i];
	}
	double tm = timer.TimerFinish();
	cout << "the original approach takes: " << tm << std::endl;
	MyTimer timer1;
	tm = 0;
	timer1.TimerStart();
	double sum = avx_sum_calc_d(ran_arr, NUM);
	tm = timer1.TimerFinish();
	cout << "the avx double approach takes:      " << tm << std::endl;

	tm = 0;
	timer1.TimerStart();
	float sum3 = avx_sum_calc_s(ran_arr_float, NUM);
	tm = timer1.TimerFinish();
	cout << "the avx float approach takes:      " << tm << std::endl;

	cout << "the sum2  by original method is : " << endl;
	printf("%.16f\n", sum2);

	cout << "the sum by avx double instruction is : " << endl;
	printf("%.16f\n", sum);

	cout << "the sum3 by avx float instruction is : " << endl;
	printf("%.16f\n", sum3);

	return 0;
}