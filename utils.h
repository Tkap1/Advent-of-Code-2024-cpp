
#define assert(cond) if(!(cond)) { on_failed_assert(#cond, __FILE__, __FUNCTION__, __LINE__); }

#define array_count(arr) (sizeof((arr)) / sizeof((arr)[0]))


struct s_v4i
{
	s_v2i a;
	s_v2i b;

	u32 hash(int n) {
		return a.hash(n) + b.hash(n);
	}
};

global s_v2i offsets_8[] = {
	{-1, -1}, {0, -1}, {1, -1},
	{-1, 0},              {1, 0},
	{-1, 1}, {0, 1}, {1, 1},
};

global s_v2i offsets_4[] = {
							{0, -1},
	{-1, 0},              {1, 0},
							{0, 1},
};

func int strleni(char* str);

func void consume_space(char** in_text)
{
	char* text = *in_text;
	while(*text == ' ') {
		text += 1;
	}
	*in_text = text;
}

func b8 consume_newline(char** in_text)
{
	b8 result = false;
	char* text = *in_text;
	if(*text == '\n') {
		text += 1;
		result = true;
	}
	*in_text = text;
	consume_space(in_text);
	return result;
}

func b8 consume_word(char** in_str, char* needle)
{
	char* str = *in_str;
	int needle_len = strleni(needle);
	b8 result = false;
	if(strncmp(str, needle, needle_len) == 0) {
		str += needle_len;
		result = true;
	}
	*in_str = str;
	return result;
}

func b8 is_number(char c)
{
	return c >= '0' && c <= '9';
}

func int char_to_int(char c)
{
	return c - '0';
}

int cmp_func(const void* aa, const void* bb)
{
	int* a = (int*)aa;
	int* b = (int*)bb;
	if(*a > *b) { return 1; }
	if(*a < *b) { return -1; }
	return 0;
}

func char* read_file(char* path)
{
	FILE* f = fopen(path, "r");
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);
	char* text = (char*)calloc(1, size + 1);
	fread(text, 1, size, f);
	return text;
}

func b8 consume_number(char** str, s64* out_val, b8 allow_sign)
{
	if(!allow_sign && ((*str)[0] == '-' || (*str)[0] == '+')) { return false; }
	char* end = null;
	s64 val = strtoll(*str, &end, 10);
	b8 result = false;
	if(end > *str) {
		*str = end;
		result = true;
	}
	*out_val = val;
	return result;
}

func void on_failed_assert(char* cond, char* file, char* function, int line)
{
	printf("\n--------------------------- FAILED ASSERT -----------------------------\n");
	printf("\tCondition: %s\n", cond);
	printf("\tLocation: %s(%i)\n", file, line);
	printf("\tFunction: %s\n", function);
	printf("-----------------------------------------------------------------------\n\n");
	__debugbreak();
	exit(1);
}

func char** get_lines(char* str, int* out_line_count)
{
	char** result = (char**)calloc(1, sizeof(char*) * 16384);
	char* cursor = str;
	int count = 0;
	char* curr_start = str;
	while(true) {
		b8 add_line = false;
		b8 found_end = false;
		char c = *cursor;
		if(c == '\0') {
			add_line = true;
			found_end = true;
		}
		else if(c == '\n') {
			add_line = true;
		}
		else {
			cursor += 1;
		}
		if(add_line) {
			int len = (int)(cursor - curr_start);
			assert(len >= 0);
			if(len > 0) {
				result[count] = (char*)calloc(1, len + 1);
				memcpy(result[count], curr_start, len);
				count += 1;
				curr_start = cursor + 1;
			}
			cursor += 1;
		}
		if(found_end) {
			break;
		}
	}
	*out_line_count = count;
	return result;
}

func int strleni(char* str)
{
	return (int)strlen(str);
}

func b8 is_valid_index(s_v2i index, int x, int y)
{
	b8 result = index.x >= 0 && index.x < x && index.y >= 0 && index.y < y;
	return result;
}

func s64 concat_nums_str(s64 a, s64 b)
{
	assert(a >= 0);
	assert(b >= 0);
	char buffer[32] = zero;
	sprintf(buffer, "%lli%lli", a, b);
	char* end = null;
	s64 result = strtoll(buffer, &end, 10);
	return result;
}

func s64 concat_nums(s64 a, s64 b)
{
	assert(a >= 0);
	assert(b >= 0);
	s64 result = b;
	int digits = 1;
	while(b >= 10) {
		b /= 10;
		digits += 1;
	}
	result += a * (s64)pow(10, digits);
	return result;
}

func s64 how_many_digits(s64 val)
{
	assert(val >= 0);
	s64 digits = 1;
	while(val >= 10) {
		val /= 10;
		digits += 1;
	}
	return digits;
}

func b8 is_letter(char c)
{
	b8 result = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
	return result;
}

func b8 is_alpha_numeric(char c)
{
	b8 result = is_number(c) || is_letter(c);
	return result;
}

func b8 operator==(s_v4i a, s_v4i b)
{
	b8 result = a.a == b.a && a.b == b.b;
	return result;
}