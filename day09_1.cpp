
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
	char* text = read_file("data09.txt");

	int line_count = 0;
	char** lines = get_lines(text, &line_count);
	s64 result = 0;

	int line_len = -1;

	struct s_block
	{
		s64 len;
		s64 id;
	};

	s_list<s_block, 209600> list = zero;

	b8 is_free = false;
	int index = 0;
	while(*text) {
		s64 val = *text - '0';
		if(!is_free) {
			for(int i = 0; i < val; i += 1) {
				list.add({val, index});
			}
			index += 1;
		}
		else {
			for(int i = 0; i < val; i += 1) {
				list.add({-1, -1});
			}
		}
		is_free = !is_free;
		text += 1;
	}

	{
		int i = 0;
		int j = list.count - 1;
		while(i < j) {
			while(list[i].len != -1) {
				i += 1;
			}
			while(list[j].len == -1) {
				j -= 1;
			}
			if(i >= j) { break; }
			list[i] = list[j];
			list[j].len = -1;
		}
	}

	foreach_val(num_i, num, list) {
		if(num.len == -1) { break; }
		result += num_i * num.id;
	}

	QueryPerformanceCounter((LARGE_INTEGER*)&after);
	printf("%f seconds\n", (after - before) / (f64)freq);
	printf("%lli\n", result);
}