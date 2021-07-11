internal TTF_Font*
load_font(const char* path, int size) {
	auto font = TTF_OpenFont(path, size);
	if (!font) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		exit(3);
	}

	return font;
}