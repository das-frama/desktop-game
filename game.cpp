internal void
update_game(f32 dt) {
	clear_screen(SDL_Color{ 0x73, 0x9A, 0xAE });

	SDL_Rect rect = { 0, 0, CLIENT_WIDTH, 50 };
	draw_rect(rect, SDL_Color{ 0xFF, 0xF8, 0xEF }, true);
}