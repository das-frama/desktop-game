internal void
clear_screen(SDL_Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(renderer);
}


internal void
draw_rect(SDL_Rect rect, SDL_Color color, bool fill = false) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	if (fill) {
		SDL_RenderFillRect(renderer, &rect);
	}
	else {
		SDL_RenderDrawRect(renderer, &rect);
	}
}
