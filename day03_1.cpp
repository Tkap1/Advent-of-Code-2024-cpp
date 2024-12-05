
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

	while(*text) {
		char* cursor = strstr(text, "mul(");
		if(!cursor) { break; }
		cursor += 4;
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

		result += a * b;

		bad:;
	}

	printf("%lli\n", result);
}