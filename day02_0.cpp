
#include <stdlib.h>
#include <stdio.h>

#include "tk_types.h"
#include "utils.h"

int main()
{
	FILE* f = fopen("data02.txt", "r");
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);
	char* text = (char*)calloc(1, size + 1);
	fread(text, 1, size, f);

	s64 result = 0;

	int iter = 0;
	int prev = 0;
	b8 ok = true;
	b8 ascending = true;
	while(*text) {
		char* end = null;
		int value = strtoll(text, &end, 10);
		if(!end) { break; }
		text = end;

		if(iter > 0) {
			b8 curr_ascending = !(prev > value);
			int diff = abs(prev - value);
			if(iter == 1) {
				ascending = curr_ascending;
			}
			else {
				if(curr_ascending != ascending) { ok = false; }
			}
			if(diff > 3) { ok = false; }
			if(diff < 1) { ok = false; }
		}
		prev = value;
		iter += 1;

		consume_space(&text);
		if(consume_newline(&text)) {
			if(ok) {
				result += 1;
			}
			iter = 0;
			ok = true;
		}
	}

	printf("%lli\n", result);
}