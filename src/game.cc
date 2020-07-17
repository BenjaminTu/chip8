#include <iostream>
#include <string>
#include "game.h"

Game::Game() {
	quit = false;
	window = SDL_CreateWindow("Chip8", 
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		std::cerr << SDL_GetError();
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, 
									SDL_TEXTUREACCESS_STREAMING, DISPLAY_WIDTH, 
									DISPLAY_HEIGHT);
}

Game::~Game() {
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Game::toQuit() {
	return quit;
}

void Game::loadGame(std::string game) {
	chip8.loadRom(game);
}

void Game::updateGfx(void const* buffer, int pitch) {
	SDL_UpdateTexture(texture, nullptr, buffer, pitch);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
	SDL_RenderPresent(renderer);
}

void Game::getKey() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		SDL_Keycode key = event.key.keysym.sym;
		switch(event.type) {
			case SDL_QUIT: 
				quit = true;
			break;

			case SDL_KEYDOWN:
				if (key == SDLK_ESCAPE) {
					quit = true;
				}

				if (key_map.find(key) == key_map.end()){
					break;
				}

				// if pressed mapped keys
				chip8.keyboard[key_map[key]] = 1;
			break;

			case SDL_KEYUP:
				if (key_map.find(key) == key_map.end()) {
					break;
				}
				// if pressed mapped keys
				chip8.keyboard[key_map[key]] = 0;
			break;
		}
	}
}

void Game::run(int delay) {
	// precision: milliseconds
	unsigned int lastTime = 0, curTime;
	while (!toQuit()) {
		getKey();
		updateGfx(chip8.display, sizeof(chip8.display[0]) * DISPLAY_WIDTH);

		curTime = SDL_GetTicks();

		if (curTime - lastTime < delay) {
			// delay between each instructions
			continue;
		}

		lastTime = curTime;
		chip8.cycle();

	}
}