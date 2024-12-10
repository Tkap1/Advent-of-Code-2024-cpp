
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

global constexpr int n = 47;
global int arr[n][n] = zero;

func b8 do_thing(s_v2i index, int target_val, s_v2i end_pos)
{
	if(index == end_pos) { return true; }
	for(int i = 0; i < 4; i += 1) {
		s_v2i pos = index + offsets_4[i];
		if(is_valid_index(pos, n, n)) {
			if(arr[pos.y][pos.x] == target_val) {
				if(do_thing(pos, target_val + 1, end_pos)) {
					return true;
				}
			}
		}
	}
	return false;
};

int main()
{
	u64 before, after, freq;
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	QueryPerformanceCounter((LARGE_INTEGER*)&before);
	char* text = read_file("data10.txt");

	int line_count = 0;
	char** lines = get_lines(text, &line_count);
	s64 result = 0;

	int line_len = -1;

	struct s_node
	{
		int curr;
		s_v2i pos;
	};

	s_list<s_node, 1024> zero_arr = zero;
	s_list<s_node, 1024> nine_arr = zero;

	for(int line_i = 0; line_i < line_count; line_i += 1) {
		char* line = lines[line_i];
		for(int i = 0; i < n; i += 1) {
			arr[line_i][i] = char_to_int(line[i]);
			if(arr[line_i][i] == 0) {
				zero_arr.add({0, v2i(i, line_i)});
			}
			if(arr[line_i][i] == 9) {
				nine_arr.add({9, v2i(i, line_i)});
			}
		}
	}


	foreach_val(zero_i, zzero, zero_arr) {
		foreach_val(nine_i, nine, nine_arr) {
			if(do_thing(zzero.pos, 1, nine.pos)) {
				result += 1;
			}
		}
	}


	QueryPerformanceCounter((LARGE_INTEGER*)&after);
	printf("%f seconds\n", (after - before) / (f64)freq);
	printf("%lli\n", result);
}