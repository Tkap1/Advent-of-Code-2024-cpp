
#define assert(cond) if(!(cond)) { on_failed_assert(#cond, __FILE__, __FUNCTION__, __LINE__); }

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

func b8 is_number(char c)
{
	return c >= '0' && c <= '9';
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

func b8 consume_number(char** str, int* out_val)
{
	char* end = null;
	int val = (int)strtoll(*str, &end, 10);
	b8 result = false;
	if(end) {
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
	exit(1);
}