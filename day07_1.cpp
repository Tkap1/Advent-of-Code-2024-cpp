
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

		s_list<s64, 128> nums = zero;
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
			s64 max_val = (s64)pow(2, nums.count - 1);
			s64 curr_val = 0;
			while(curr_val <= max_val) {
				s64 temp_result = nums[0];

				for(int num_i = 1; num_i < nums.count; num_i += 1) {
					s64 a = nums[num_i];

					s64 mask = 1LL << (num_i - 1);
					s64 bit = curr_val & mask;
					if(bit) {
						temp_result *= a;
					}
					else {
						temp_result += a;
					}
				}
				if(temp_result == wanted) {
					result += wanted;
					break;
				}
				else {
					curr_val += 1;
				}
			}
		}
	}

	printf("%lli\n", result);
}