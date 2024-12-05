
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tk_types.h"
#include "utils.h"

int main()
{
	FILE* f = fopen("data03.txt", "r");
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);
	char* text = (char*)calloc(1, size + 1);
	fread(text, 1, size, f);

	s64 result = 0;

	b8 enabled = true;

	while(*text) {
		if(strncmp(text, "do()", 4) == 0) {
			enabled = true;
			text += 4;
			continue;
		}
		if(strncmp(text, "don't()", 7) == 0) {
			enabled = false;
			text += 7;
			continue;
		}
		if(strncmp(text, "mul(", 4) == 0) {
			char* cursor = text + 4;
			text = cursor;
			char* end = null;
			int a = strtoll(cursor, &end, 10);
			if(end == null) { goto bad; }
			cursor = end;
			if(*cursor != ',') { goto bad; }
			cursor += 1;
			end = null;
			int b = strtoll(cursor, &end, 10);
			if(end == null) { goto bad; }
			cursor = end;
			if(*cursor != ')') { goto bad; }
			cursor += 1;

			text = cursor;
			if(enabled) {
				result += a * b;
			}
			bad:;

			continue;
		}
		else {
			text +=1;
		}
	}

	printf("%lli\n", result);
}