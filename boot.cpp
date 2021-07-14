#define DOTS_SPEED 500

struct Boot_State {
	bool is_initialized = false;
	bool is_printing = true;
	int current_message = 0;
	float acc;
} boot_state;

struct Boot_Message {
	const char* text = nullptr;
	int time = 1000;
	int delay = 1000;
	bool is_printed = false;
};

Boot_Message boot_messages[] = {
	{"Загрузка первичных драйверов", 1500, 1000},
	{"Загрузка основных компонентов", 1000, 1000},
	{"Проверка подписи", 2600, 1000},
	{"Завершено...", 0, 0},
};
int messages_count = sizeof(boot_messages) / sizeof(boot_messages[0]);

inline char*
dots(const Boot_Message& message) {
	u8 count = 0;
	if (message.is_printed) {
		count = message.time / DOTS_SPEED;
	} else {
		count = (int)boot_state.acc / DOTS_SPEED;
	}

	auto buf = (char*)malloc((count + 1) * sizeof(char));
	for (int i = 0; i < count; i++) {
		*(buf + i) = '.';
	}
	*(buf + count) = '\0';

	return buf;
}

internal void
update_boot(f32 dt) {
	// Accumalte dt.
	if (boot_state.is_printing) {
		boot_state.acc += dt;

		auto message = &boot_messages[boot_state.current_message];
		if (boot_state.acc >= message->time) {
			message->is_printed = true;
			if (boot_state.acc >= message->time + message->delay) {
				boot_state.acc = 0;
				boot_state.current_message += 1;
			}
		}

		if (boot_state.current_message >= messages_count) {
			boot_state.current_message = messages_count - 1;
			boot_state.is_printing = false;
			//boot_state.is_initialized = true;
		}
	}

	// Draw text to the screen.
	{
		clear_screen(SDL_Color{ 0x0, 0x0, 0x0 });
		SDL_Color white = { 0xff, 0xff, 0xff };
		for (int i = 0; i < boot_state.current_message + 1; i++) {
			char buf[255];
			sprintf_s(buf, "%s%s", boot_messages[i].text, dots(boot_messages[i]));
			draw_text(buf, desktop_font, 15, 15 * i + (i * 15), white);
		}
	}
}
