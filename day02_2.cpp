
#include <stdlib.h>
#include <stdio.h>

#include "tk_types.h"
#include "utils.h"

b8 passes_test(int* arr, int count, int blacklist)
{
	int prev = 0;
	b8 ascending = true;
	b8 ok = true;
	b8 have_ascending = false;
	b8 have_prev = false;
	for(int i = 0; i < count; i += 1) {
		if(i == blacklist) { continue; }
		int value = arr[i];
		if(have_prev) {
			b8 curr_ascending = !(prev > value);
			int diff = abs(prev - value);
			if(!have_ascending) {
				ascending = curr_ascending;
				have_ascending = true;
			}
			else {
				if(curr_ascending != ascending) { ok = false; }
			}
			if(diff > 3) { ok = false; }
			if(diff < 1) { ok = false; }
		}
		prev = value;
		have_prev = true;
	}
	return ok;
}


int main()
{
	FILE* f = fopen("data02.txt", "r");
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);
	char* text = (char*)calloc(1, size + 1);
	fread(text, 1, size, f);

	int arr[1024] = zero;
	int count = 0;

	s64 result = 0;

	while(*text) {
		char* end = null;
		int value = strtoll(text, &end, 10);
		if(!end) { break; }
		arr[count] = value;
		count += 1;
		text = end;

		consume_space(&text);
		if(consume_newline(&text)) {
			if(passes_test(arr, count, -1)) {
				result += 1;
			}
			else {
				for(int i = 0; i < count; i += 1) {
					if(passes_test(arr, count, i)) {
						result += 1;
						break;
					}
				}
			}
			count = 0;
		}
	}

	printf("%lli\n", result);
}