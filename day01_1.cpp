
#include <stdlib.h>
#include <stdio.h>

#include "tk_types.h"
#include "utils.h"

int main()
{
	FILE* f = fopen("data01.txt", "r");
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);
	char* text = (char*)calloc(1, size + 1);
	fread(text, 1, size, f);

	int* left_arr = (int*)calloc(1, 1000 * sizeof(int));
	int* right_arr = (int*)calloc(1, 1000 * sizeof(int));
	int lcount = 0;
	int rcount = 0;

	b8 bar = true;
	while(*text) {
		char* end = null;
		s64 foo = strtoll(text, &end, 10);
		if(!end) { break; }
		text = end;
		if(bar) {
			left_arr[lcount] = foo;
			lcount += 1;
		}
		else {
			right_arr[rcount] = foo;
			rcount += 1;
		}
		bar = !bar;
		while(*text == ' ' || *text == '\n' || *text == '\r') {
			text += 1;
		}
	}

	s64 result = 0;
	for(int i = 0; i < lcount; i += 1) {
		int l = left_arr[i];
		int count = 0;
		for(int j = 0; j < lcount; j += 1) {
			int r = right_arr[j];
			if(l == r) {
				count += 1;
			}
		}
		result += l * count;
	}

	printf("%lli\n", result);
}