
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

	char* text = read_file("data08.txt");

	int line_count = 0;
	char** lines = get_lines(text, &line_count);
	s64 result = 0;

	int line_len = -1;

	constexpr int n = 50;

	char ant_arr[n][n] = zero;
	char anti_arr[n][n] = zero;

	s_hashmap<s_v4i, b8, 2048> map = zero;

	for(int line_i = 0; line_i < line_count; line_i += 1) {
		char* base_line = lines[line_i];
		char* line = lines[line_i];
		int len = strleni(line);
		if(line_len == -1) {
			line_len = len;
		}

		for(int i = 0; i < n; i += 1) {
			if(is_alpha_numeric(line[i])) {
				ant_arr[line_i][i] = line[i];
			}
		}
	}

	for(int y0 = 0; y0 < n; y0 += 1) {
		for(int x0 = 0; x0 < n; x0 += 1) {
			char c0 = ant_arr[y0][x0];
			if(c0 == '\0') { continue; }
			s_v2i a = v2i(x0, y0);
			for(int y1 = 0; y1 < n; y1 += 1) {
				for(int x1 = 0; x1 < n; x1 += 1) {
					s_v2i b = v2i(x1, y1);
					if(a == b) { continue; }
					char c1 = ant_arr[y1][x1];
					if(c1 == '\0') { continue; }
					if(hashmap_get(&map, {a, b}) || hashmap_get(&map, {b, a})) { continue; }
					if(c0 == c1) {
						hashmap_set(&map, {a, b}, true);
						s_v2i offset = v2i(
							x1 - x0,
							y1 - y0
						);

						{
							s_v2i temp_pos = a + offset;
							while(true) {
								if(!is_valid_index(temp_pos, n, n)) { break; }
								anti_arr[temp_pos.y][temp_pos.x] = c0;
								temp_pos = temp_pos + offset;
							}
						}

						{
							s_v2i temp_pos = b - offset;
							while(true) {
								if(!is_valid_index(temp_pos, n, n)) { break; }
								anti_arr[temp_pos.y][temp_pos.x] = c0;
								temp_pos = temp_pos - offset;
							}
						}
					}
				}
			}
		}
	}

	for(int y = 0; y < n; y += 1) {
		for(int x = 0; x < n; x += 1) {
			if(anti_arr[y][x] != '\0') {
				result += 1;
			}
		}
	}

	QueryPerformanceCounter((LARGE_INTEGER*)&after);
	printf("%f seconds\n", (after - before) / (f64)freq);
	printf("Expecting 9\n");
	printf("%lli\n", result);
}