
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "tk_types.h"
#include "utils.h"

#define m_tk_math_impl
#include "tk_math.h"

#define m_tk_array_impl
#include "tk_array.h"

#define m_tk_hashmap_impl
#include "tk_hashmap.h"


int main()
{
	char* text = read_file("data05.txt");

	s64 result = 0;

	struct s_update
	{
		s_list<int, 32> nums;
	};
	s_list<s_update, 2048> updates = zero;
	s_list<s_update, 2048> bad_updates = zero;
	s_hashmap<s_v2i, b8, 2048> map = zero;

	while(true) {
		if(consume_newline(&text)) { break; }

		int a, b;
		consume_number(&text, &a);
		text += 1;
		consume_number(&text, &b);

		hashmap_set(&map, v2i(a, b), true);

		consume_newline(&text);
	}

	s_update update = zero;
	while(*text) {
		if(consume_newline(&text)) { break; }
		int a;
		consume_number(&text, &a);

		update.nums.add(a);

		if(consume_newline(&text)) {
			updates.add(update);
			update = zero;
		}
		else {
			text += 1;
		}
	}

	foreach_val(update_i, update, updates) {
		b8 ok = true;
		foreach_ptr(n_i, n, update.nums) {
			for(int n2_i = n_i + 1; n2_i < update.nums.count; n2_i += 1) {
				int *n2 = &update.nums[n2_i];
				if(hashmap_get(&map, v2i(*n2, *n))) {
					swap(n, n2);
					ok = false;
				}
			}
		}
		if(!ok) {
			result += update.nums[update.nums.count / 2];
		}
	}

	printf("%lli\n", result);
}