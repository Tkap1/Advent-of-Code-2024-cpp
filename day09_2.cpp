
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
		if(!is_number(*text)) { break; }
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
		struct s_free
		{
			int len;
			int index;
		};
		int j = list.count - 1;
		while(true) {
			while(list[j].len == -1) {
				j -= 1;
			}
			s_list<s_free, 209600> free_list = zero;
			foreach_val(num_i, num, list) {
				if(num_i >= j) { continue; }
				if(num.len == -1) {
					s_free new_free = zero;
					new_free.index = num_i;
					for(int k = num_i; k < list.count; k += 1) {
						if(list[k].len == -1) {
							new_free.len += 1;
						}
						else { break; }
					}
					num_i += new_free.len - 1;
					free_list.add(new_free);
				}
			}

			if(free_list.count <= 0) { break; }
			if(free_list[0].index > j) { break; }
			b8 fit = false;
			foreach_val(freee_i, freee, free_list) {
				s_block temp_block = list[j];
				if(freee.len >= temp_block.len) {
					fit = true;
					for(int k = 0; k < temp_block.len; k += 1) {
						list[freee.index + k] = temp_block;
						list[j] = {-1, -1};
						j -= 1;
					}
					break;
				}
			}
			if(!fit) {
				j -= list[j].len;
			}
		}
	}

	foreach_val(num_i, num, list) {
		if(num.len == -1) { continue; }
		result += num_i * num.id;
	}

	QueryPerformanceCounter((LARGE_INTEGER*)&after);
	printf("%f seconds\n", (after - before) / (f64)freq);
	printf("%lli\n", result);
}