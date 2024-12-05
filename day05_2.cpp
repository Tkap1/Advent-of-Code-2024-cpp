
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tk_types.h"
#define assert(...)
#define m_tk_array_impl
#include "tk_array.h"

#include "utils.h"

int main()
{
	char* text = read_file("data05.txt");

	s64 result = 0;

	struct s_rule
	{
		int a;
		int b;
	};
	struct s_update
	{
		s_list<int, 32> nums;
	};
	s_list<s_rule, 2048> rules = zero;
	s_list<s_update, 2048> updates = zero;
	s_list<s_update, 2048> bad_updates = zero;

	while(true) {
		if(consume_newline(&text)) { break; }

		int a, b;
		consume_number(&text, &a);
		text += 1;
		consume_number(&text, &b);

		rules.add({a, b});

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
		foreach_val(n_i, n, update.nums) {
			foreach_val(n2_i, n2, update.nums) {
				if(n_i == n2_i) { continue; }
				foreach_val(rule_i, rule, rules) {
					if(rule.a == n && rule.b == n2) {
						if(!(n_i < n2_i)) { ok = false; }
					}
					if(rule.a == n2 && rule.b == n) {
						if(!(n2_i < n_i)) { ok = false; }
					}
				}
			}
		}
		if(!ok) {
			bad_updates.add(update);
		}
	}

	auto fn = [&rules](int* a, int* b){
		foreach_val(rule_i, rule, rules) {
			if(rule.a == *a && rule.b == *b) {
				return false;
			}
			if(rule.a == *b && rule.b == *a) {
				return true;
			}
		}
		return false;
	};

	foreach_val(update_i, update, bad_updates) {
		bubble_sort_list(&update.nums, fn);
		result += update.nums[update.nums.count / 2];
	}

	printf("%lli\n", result);
}