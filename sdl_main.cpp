#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// This is a UNITY build!
#include "utils.cpp"
#include "string.cpp"

// Defines.
#define CLIENT_WIDTH 1920
#define CLIENT_HEIGHT 1080

// Here lies the globals that used in our game.
global_variable bool game_is_running = false;
global_variable SDL_Renderer* renderer = { 0 };
global_variable u64 frequence_counter = 0;
global_variable TTF_Font* desktop_font = nullptr;

// This is a UNITY build!
#include "asset_loader.cpp"
#include "renderer.cpp"
#include "game.cpp"

// Semi-globals.
SDL_Window* window = { 0 };
u64 now_time = SDL_GetPerformanceCounter();
u64 last_time = 0;
f32 last_dt = 0;

// Init all the SDL things...
void init_game(const char* title) {
	printf("Initializing game...\n");

	// Counters.
	frequence_counter = SDL_GetPerformanceFrequency();

	// Init SDL libs.
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		IMG_Init(IMG_INIT_PNG);
		TTF_Init();
	}

	// Init window and renderer.
	{
		// Ofcourse we need a window to create...
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, CLIENT_WIDTH, CLIENT_HEIGHT, SDL_WINDOW_VULKAN);
		if (window == nullptr) {
			printf("Failed to create window: %s\n", SDL_GetError());
			exit(-1);
		}
		// And then a renderer where we draw stuff.
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
		if (renderer == nullptr) {
			printf("Failed to create renderer: %s\n", SDL_GetError());
			exit(-1);
		}
	}

	// Init some stuff...
	{
		SDL_RenderSetLogicalSize(renderer, CLIENT_WIDTH, CLIENT_HEIGHT);
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
	}

	// Load resources.
	{
		desktop_font = load_font("data/fonts/clacon.ttf", 32);
	}

	game_is_running = true;
}

// Quit and clean all things of SDL...
void close_game() {
	printf("Quiting game...\n");

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

internal void
process_events() {
	// Poll events...
	SDL_Event event = { 0 };
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
			game_is_running = false;
		}
		else if (event.key.keysym.sym == SDLK_F1) {
			change_game_mode(GM_MENU);
		}
		else if (event.key.keysym.sym == SDLK_F2) {
			change_game_mode(GM_DESKTOP);
		}
	}
}

internal void
do_one_frame() {
	// Start time.
	last_time = now_time;
	now_time = SDL_GetPerformanceCounter();

	// Events.
	process_events();

	// Clear renderer to black.
	SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
	SDL_RenderClear(renderer);

	// Simulation.
	update_game(last_dt);

	// Render.
	SDL_RenderPresent(renderer);

	// Get frame time.
	u64 end = SDL_GetPerformanceCounter();
	last_dt = (now_time - last_time) * 1000 / (f32)frequence_counter;

	/*char buf[80];
	sprintf_s(buf, "dt = %f.2", last_dt);
	SDL_SetWindowTitle(window, buf);*/
}

int main(int argc, char* argv[]) {
	// Init SDL.
	init_game("Desktop Game");

	// Game loop.
	while (game_is_running) {
		do_one_frame();
	}

	// Clear all resources.
	close_game();

	return 0;
}
