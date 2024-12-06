
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
	s_v2i offsets_8[] = {
		v2i(-1, -1), v2i(0, -1), v2i(1, -1),
		v2i(-1, 0),              v2i(1, 0),
		v2i(-1, 1), v2i(0, 1), v2i(1, 1),
	};

	s_v2i offsets_4[] = {
		            v2i(0, -1),
		v2i(-1, 0),              v2i(1, 0),
		            v2i(0, 1),
	};

	char* text = read_file("data06.txt");

	int line_count = 0;
	char** lines = get_lines(text, &line_count);
	s64 result = 0;

	int line_len = -1;
	s_v2i base_guard_pos;
	enum {up, right,down, left};
	s_v2i offsets[] = {v2i(0, -1), v2i(1, 0), v2i(0, 1), v2i(-1, 0)};
	int base_guard_dir = up;
	b8 base_obstacle_arr[200][200] = zero;
	struct s_dir {
		b8 valid;
		int dir;
	};
	s_dir base_visit_arr[200][200] = zero;
	int steps = 0;

	for(int line_i = 0; line_i < line_count; line_i += 1) {
		char* base_line = lines[line_i];
		char* line = lines[line_i];
		int len = strleni(line);
		if(line_len == -1) {
			line_len = len;
		}

		while(*line) {
			int x = (int)(line - base_line);
			if(*line == '#') {
				base_obstacle_arr[line_i][x] = true;
				line += 1;
			}
			else if(*line == '^') {
				base_guard_pos = v2i(x, line_i);
				base_guard_dir = up;
				line += 1;
			}
			else if(*line == 'v') {
				base_guard_pos = v2i(x, line_i);
				base_guard_dir = down;
				line += 1;
			}
			else if(*line == '<') {
				base_guard_pos = v2i(x, line_i);
				base_guard_dir = left;
				line += 1;
			}
			else if(*line == '>') {
				base_guard_pos = v2i(x, line_i);
				base_guard_dir = right;
				line += 1;
			}
			else {
				line += 1;
			}
		}
	}

	{
		s_v2i guard_pos = base_guard_pos;
		int guard_dir = base_guard_dir;
		base_visit_arr[guard_pos.y][guard_pos.x] = {true, guard_dir};
		while(true) {
			s_v2i next_pos = guard_pos + offsets[guard_dir];
			if(is_valid_index(next_pos, line_len, line_count) && base_obstacle_arr[next_pos.y][next_pos.x]) {
				guard_dir = (guard_dir + 1) % 4;
				steps += 1;
			}
			else {
				guard_pos = guard_pos + offsets[guard_dir];
				if(!is_valid_index(guard_pos, line_len, line_count)) {
					break;
				}
				else {
					base_visit_arr[guard_pos.y][guard_pos.x] = {true, guard_dir};
				}
			}
		}
	}

	int loop_count = 0;
	for(int y = 0; y < line_count; y += 1) {
		for(int x = 0; x < line_len; x += 1) {
			s_v2i index = v2i(x, y);
			if(!base_obstacle_arr[y][x] && v2i(x, y) != base_guard_pos) {
				// printf("%i, %i\n", x, y);
				if(!base_visit_arr[index.y][index.x].valid) { continue; };

				b8 obstacle_arr[200][200];
				memcpy(obstacle_arr, base_obstacle_arr, sizeof(obstacle_arr));
				s_v2i guard_pos = base_guard_pos;
				int guard_dir = base_guard_dir;
				b8 in_a_loop = false;

				s_dir visit_arr[200][200] = zero;
				visit_arr[guard_pos.y][guard_pos.x] = {true, guard_dir};
				obstacle_arr[y][x] = true;

				while(true) {
					s_v2i next_pos = guard_pos + offsets[guard_dir];
					if(is_valid_index(next_pos, line_len, line_count) && obstacle_arr[next_pos.y][next_pos.x]) {
						guard_dir = (guard_dir + 1) % 4;
						steps += 1;
					}
					else {
						guard_pos = next_pos;
						if(!is_valid_index(guard_pos, line_len, line_count)) {
							break;
						}
						else {
							s_dir prev_dir = visit_arr[guard_pos.y][guard_pos.x];
							if(prev_dir.valid && prev_dir.dir == guard_dir) {
								in_a_loop = true;
								loop_count += 1;
								break;
							}
							visit_arr[guard_pos.y][guard_pos.x] = {true, guard_dir};
						}
					}
				}
			}
		}
	}

	result = loop_count;

	printf("%lli\n", result);
}