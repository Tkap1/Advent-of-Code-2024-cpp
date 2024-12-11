
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "tk_types.h"

#define m_tk_math_impl
#include "tk_math.h"
#include "utils.h"

#define m_tk_array_impl
#include "tk_array.h"

#define m_tk_hashmap_impl
#include "tk_hashmap.h"

int main()
{
	u64 before, after, freq;
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	QueryPerformanceCounter((LARGE_INTEGER*)&before);
	char* text = read_file("data11.txt");

	int line_count = 0;
	char** lines = get_lines(text, &line_count);
	s64 result = 0;

	int line_len = -1;

	s_list<s64, 524288> arr = {8, {1, 24596, 0, 740994, 60, 803, 8918, 9405859}};

	constexpr int blinks = 25;
	for(int i = 0; i < blinks; i += 1) {
		foreach_ptr(n_i, n, arr) {
			if(*n == 0) {
				*n = 1;
				continue;
			}
			s64 digits = how_many_digits(*n);
			if(digits % 2 == 0) {
				char buffer[1024] = zero;
				sprintf(buffer, "%lli", *n);
				char left[512] = zero;
				char right[512] = zero;
				memcpy(left, buffer, digits / 2);
				memcpy(right, buffer + digits / 2, digits / 2);
				s64 left_val = strtoll(left, null, 10);
				s64 right_val = strtoll(right, null, 10);
				*n = left_val;
				list_insert(&arr, n_i + 1, right_val);
				n_i += 1;
				continue;
			}
			*n = *n * 2024;
		}
	}

	result = arr.count;


	QueryPerformanceCounter((LARGE_INTEGER*)&after);
	printf("%f seconds\n", (after - before) / (f64)freq);
	printf("%lli\n", result);
}