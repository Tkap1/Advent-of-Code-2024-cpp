
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
	s_v2i guard_pos;
	enum {up, right,down, left};
	s_v2i offsets[] = {v2i(0, -1), v2i(1, 0), v2i(0, 1), v2i(-1, 0)};
	int guard_dir = up;
	s_hashmap<s_v2i, b8, 20480> obstacle_map = zero;
	s_hashmap<s_v2i, b8, 20480> visit_map = zero;
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
				hashmap_set(&obstacle_map, v2i(x, line_i), true);
				line += 1;
			}
			else if(*line == '^') {
				guard_pos = v2i(x, line_i);
				guard_dir = up;
				line += 1;
			}
			else if(*line == 'v') {
				guard_pos = v2i(x, line_i);
				guard_dir = down;
				line += 1;
			}
			else if(*line == '<') {
				guard_pos = v2i(x, line_i);
				guard_dir = left;
				line += 1;
			}
			else if(*line == '>') {
				guard_pos = v2i(x, line_i);
				guard_dir = right;
				line += 1;
			}
			else {
				line += 1;
			}
		}
	}

	hashmap_set(&visit_map, guard_pos, true);
	while(true) {
		if(hashmap_get(&obstacle_map, guard_pos + offsets[guard_dir])) {
			guard_dir = (guard_dir + 1) % 4;
			steps += 1;
		}
		else {
			guard_pos = guard_pos + offsets[guard_dir];
			if(!is_valid_index(guard_pos, line_len, line_count)) {
				break;
			}
			else {
				hashmap_set(&visit_map, guard_pos, true);
			}
		}
	}

	result = visit_map.used_count;

	// while(*line

	printf("%lli\n", result);
}