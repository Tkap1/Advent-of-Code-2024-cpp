
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

global s_list<s64, 128> nums = zero;

s64 do_op(s64 a, s64 b, int op)
{
	s64 c;
	if(op == 0) {
		c = a + b;
	}
	else if(op == 1) {
		c = a * b;
	}
	else if(op == 2) {
		char buffer[32] = zero;
		sprintf(buffer, "%lli%lli", a, b);
		char* temp_str = buffer;
		consume_number(&temp_str, &c, false);
	}
	return c;
}

s64 solve(s64 curr, int i, int op, s64 wanted)
{
	if(i >= nums.count) { return -1; }
	s64 base = do_op(curr, nums[i], op);
	if(base > wanted) { return -1; }
	if(base == wanted && i == nums.count - 1) { return base; }
	if(i + 1 < nums.count) {
		for(int op_i = 0; op_i < 3; op_i += 1) {
			s64 t = solve(base, i + 1, op_i, wanted);
			if(t == wanted) { return t; }
		}
	}
	return -1;
}

int main()
{
	char* text = read_file("data07.txt");

	int line_count = 0;
	char** lines = get_lines(text, &line_count);
	s64 result = 0;

	int line_len = -1;

	for(int line_i = 0; line_i < line_count; line_i += 1) {
		char* base_line = lines[line_i];
		char* line = lines[line_i];
		int len = strleni(line);
		if(line_len == -1) {
			line_len = len;
		}
		nums = zero;

		while(*line) {
			s64 wanted = 0;
			if(!consume_number(&line, &wanted, false)) {
				break;
			}
			line += 2;
			while(true) {
				s64 n;
				if(!consume_number(&line, &n, false)) {
					line += 1;
					break;
				}
				nums.add(n);
				consume_space(&line);
			}

			for(int op_i = 0; op_i < 3; op_i += 1) {
				s64 temp = solve(nums[0], 1, op_i, wanted);
				if(temp == wanted) {
					result += wanted;
					break;
				}
			}
		}
	}

	printf("%lli\n", result);
}