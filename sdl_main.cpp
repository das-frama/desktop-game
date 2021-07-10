#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// Here lies the globals that used in our game.
bool game_is_running = false;


// Init all the SDL things...
void sdl_init(const char* title, int w, int h, SDL_Renderer* renderer, SDL_Window* window) {
	printf("Initializing game...\n");

	// Main SDL Init...
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	// Ofcourse we need a window to create...
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		printf("Failed to create window: %s\n", SDL_GetError());
		exit(-1);
	}
	// And then a renderer where we draw stuff.
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	if (renderer == nullptr) {
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(-1);
	}

	SDL_RenderSetLogicalSize(renderer, w, h);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
	SDL_SetRenderDrawColor(renderer, 51, 102, 152, 255);

	game_is_running = true;
}

// Quit and clean all things of SDL...
void sdl_close(SDL_Renderer* renderer, SDL_Window* window) {
	printf("Quiting game...\n");

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void do_one_frame(SDL_Renderer* renderer, SDL_Event &event) {
	// Poll events...
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
			game_is_running = false;
		}
	}

	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
	// Init SDL.
	SDL_Renderer* renderer = { 0 };
	SDL_Window* window = { 0 };
	sdl_init("Desktop Game", 1280, 720, renderer, window);

	// Game loop.
	SDL_Event event = { 0 };
	while (game_is_running) {
		do_one_frame(renderer, event);
	}

	// Clear all resources.
	sdl_close(renderer, window);

	return 0;
}
