
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

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

struct s_foo
{
	s64 val;
	int blinks_left;

	bool operator==(const s_foo& other) const {
		return val == other.val && blinks_left == other.blinks_left;
	}

	u32 hash(int n)
	{
		auto A = (u32)(val >= 0 ? 2 * val : -2 * val - 1);
    auto B = (u32)(blinks_left >= 0 ? 2 * blinks_left : -2 * blinks_left - 1);
    auto C = (int)((A >= B ? A * A + A + B : A + B * B) / 2);
    return val < 0 && blinks_left < 0 || val >= 0 && blinks_left >= 0 ? C : -C - 1;
	}
};

global s_hashmap<s_foo, s64, 262144> map;

func s64 solve(s64 val, int blinks_left)
{
	if(blinks_left <= 0) { return 1; };
	s64 result = 0;

	s64 *temp = hashmap_get(&map, {val, blinks_left});
	if(temp) {
		return *temp;
	}

	if(val == 0) {
		result = solve(1, blinks_left - 1);
		hashmap_set(&map, {val, blinks_left}, result);
		goto end;
	}

	s64 digits = how_many_digits(val);
	if(digits % 2 == 0) {
		char buffer[1024] = zero;
		sprintf(buffer, "%lli", val);
		char left[512] = zero;
		char right[512] = zero;
		memcpy(left, buffer, digits / 2);
		memcpy(right, buffer + digits / 2, digits / 2);
		s64 left_val = strtoll(left, null, 10);
		s64 right_val = strtoll(right, null, 10);
		result += solve(left_val, blinks_left - 1);
		result += solve(right_val, blinks_left - 1);
		hashmap_set(&map, {val, blinks_left}, result);
		goto end;
	}

	result = solve(val * 2024, blinks_left - 1);
	hashmap_set(&map, {val, blinks_left}, result);
	goto end;

	end:
	return result;
}

int main()
{
	u64 before, after, freq;
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	QueryPerformanceCounter((LARGE_INTEGER*)&before);
	char* text = read_file("data11.txt");

	int line_count = 0;
	char** lines = get_lines(text, &line_count);
	s64 result = 0;

	int line_len = -1;

	s_list<s64, 32> arr = {8, {1, 24596, 0, 740994, 60, 803, 8918, 9405859}};

	constexpr int blinks = 75;
	foreach_val(n_i, n, arr) {
		result += solve(n, blinks);
	}

	QueryPerformanceCounter((LARGE_INTEGER*)&after);
	printf("%f seconds\n", (after - before) / (f64)freq);
	printf("%lli\n", result);
}