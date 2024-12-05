
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tk_types.h"
#include "utils.h"

int main()
{
	FILE* f = fopen("data04.txt", "r");
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);
	char* text = (char*)calloc(1, size + 1);
	fread(text, 1, size, f);

	// The size of the "square" (how many lines/how long are the lines)
	constexpr int n = 140;

	// Split input into lines
	char lines[n][n+1] = zero;
	for(int i = 0; i < n; i += 1) {
		memcpy(&lines[i][0], text + i * (n + 1), n);
	}

	s64 result = 0;

	for(int i = 0; i < n; i += 1) {
		for(int j = 0; j < n; j += 1) {
			// right
			if(
				j < n - 3 &&
				(
					lines[i][j + 0] == 'X' && lines[i][j + 1] == 'M' && lines[i][j + 2] == 'A' && lines[i][j + 3] == 'S' ||
					lines[i][j + 0] == 'S' && lines[i][j + 1] == 'A' && lines[i][j + 2] == 'M' && lines[i][j + 3] == 'X'
				)
			) {
				result += 1;
			}
			// down
			if(
				i < n - 3 &&
				(
					lines[i + 0][j] == 'X' && lines[i + 1][j] == 'M' && lines[i + 2][j] == 'A' && lines[i + 3][j] == 'S' ||
					lines[i + 0][j] == 'S' && lines[i + 1][j] == 'A' && lines[i + 2][j] == 'M' && lines[i + 3][j] == 'X'
				)
			) {
				result += 1;
			}
			// bottom right
			if(
				i < n - 3 && j < n - 3 &&
				(
					lines[i + 0][j + 0] == 'X' && lines[i + 1][j + 1] == 'M' && lines[i + 2][j + 2] == 'A' && lines[i + 3][j + 3] == 'S' ||
					lines[i + 0][j + 0] ==  'S' && lines[i + 1][j + 1] == 'A' && lines[i + 2][j + 2] == 'M' && lines[i + 3][j + 3] == 'X'
				)
			) {
				result += 1;
			}
			// bottom left
			if(
				i < n - 3 && j >= 3 &&
				(
					lines[i + 0][j - 0] == 'X' && lines[i + 1][j - 1] == 'M' && lines[i + 2][j - 2] == 'A' && lines[i + 3][j - 3] == 'S' ||
					lines[i + 0][j - 0] == 'S' && lines[i + 1][j - 1] == 'A' && lines[i + 2][j - 2] == 'M' && lines[i + 3][j - 3] == 'X'
				)
			) {
				result += 1;
			}
		}
	}

	printf("%lli\n", result);
}