
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

	constexpr int n = 140;

	char lines[n][n+1] = zero;
	for(int i = 0; i < n; i += 1) {
		memcpy(&lines[i][0], text + i * (n + 1), n);
	}

	s64 result = 0;

	for(int i = 1; i < n - 1; i += 1) {
		for(int j = 1; j < n - 1; j += 1) {
			if(lines[i][j] == 'A') {
				int m = 0;
				int s = 0;
				m += lines[i - 1][j - 1] == 'M' ? 1 : 0;
				s += lines[i - 1][j - 1] == 'S' ? 1 : 0;

				m += lines[i - 1][j + 1] == 'M' ? 1 : 0;
				s += lines[i - 1][j + 1] == 'S' ? 1 : 0;

				m += lines[i + 1][j - 1] == 'M' ? 1 : 0;
				s += lines[i + 1][j - 1] == 'S' ? 1 : 0;

				m += lines[i + 1][j + 1] == 'M' ? 1 : 0;
				s += lines[i + 1][j + 1] == 'S' ? 1 : 0;

				char topleft = lines[i - 1][j - 1];
				char bottomright = lines[i + 1][j + 1];

				if(
					m == 2 && s == 2 && topleft != bottomright
				) {
					result += 1;
				}
			}
		}
	}

	printf("%lli\n", result);
}