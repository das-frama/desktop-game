#define DOTS_SPEED 500

struct Boot_State {
	bool is_initialized = false;
	bool is_printing = true;
	int printend = 0;
	float acc;
} boot_state;

struct Boot_Message {
	const char* text = nullptr;
	int delay = 1000;
	bool is_printed = false;
};

Boot_Message boot_messages[] = {
	{"Загрузка первичных драйверов", 5000},
	{"Загрузка основных компонентов", 7000},
	{"Проверка подписи", 12000},
};


inline char*
dots(const Boot_Message &message) {
	u8 count = 0;
	if (message.is_printed) {
		count = message.delay / DOTS_SPEED;
	} else {
		count = (int) boot_state.acc / DOTS_SPEED;
	}

	auto buf = (char*)malloc((count + 1) * sizeof(char));
	for (int i = 0; i < count; i++) {
		*(buf + i) = '.';
	}
	*(buf+count) = '\0';

	return buf;
}


internal void
update_boot(f32 dt) {
	// Accumalte dt.
	{
		boot_state.acc += dt;

		if (boot_state.acc >= boot_messages[boot_state.printend].delay) {
			boot_state.acc = 0;
			boot_messages[boot_state.printend].is_printed = true;
			boot_state.printend += 1;
		}

		if (boot_state.printend >= 3) {
			boot_state.printend = 2;
			//boot_state.is_printing = false;
			//boot_state.is_initialized = true;
		}
	}

	// Draw text to the screen.
	{
		clear_screen(SDL_Color{ 0x0, 0x0, 0x0 });
		SDL_Color white = { 0xff, 0xff, 0xff };
		for (int i = 0; i < boot_state.printend + 1; i++) {
			char buf[128];
			sprintf_s(buf, "%s%s", boot_messages[i].text, dots(boot_messages[i]));
			draw_text(buf, desktop_font, 15, 15 * i + (i * 25), white);
		}
	}
}
