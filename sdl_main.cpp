#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// This is a UNITY build!
#include "utils.cpp"
#include "string.cpp"

// Defines.
#define CLIENT_WIDTH 1280
#define CLIENT_HEIGHT 720

// Here lies the globals that used in our game.
global_variable bool game_is_running = false;
global_variable SDL_Renderer* renderer = { 0 };
global_variable u64 frequence_counter = 0;

// This is a UNITY build!
#include "renderer.cpp"
#include "desktop.cpp"
#include "game.cpp"

// Semi-globals.
SDL_Window* window = { 0 };
f32 last_dt = 0;

// Init all the SDL things...
void init_game(const char* title) {
	printf("Initializing game...\n");

	// Counters.
	frequence_counter = SDL_GetPerformanceFrequency();
	//last_dt = 1.f / (f32)SDL_GetTicks

	// Main SDL Init...
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	// Ofcourse we need a window to create...
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, CLIENT_WIDTH, CLIENT_HEIGHT, SDL_WINDOW_OPENGL);
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

	SDL_RenderSetLogicalSize(renderer, CLIENT_WIDTH, CLIENT_HEIGHT);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);

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
	}
}

internal void 
do_one_frame() {
	// Start time.
	u64 start = SDL_GetPerformanceCounter();
	// Events.
	process_events();

	// Simulation.
	update_game(last_dt);

	// Render.
	SDL_RenderPresent(renderer);

	// Get frame time.
	u64 end = SDL_GetPerformanceCounter();
	last_dt = (end - start) / (f32)frequence_counter;
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
