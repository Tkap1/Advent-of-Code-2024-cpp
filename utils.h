
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
