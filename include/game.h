#include <unordered_map>
#include <SDL2/SDL.h>
#include "chip8.h"

#ifndef GAME_H
#define GAME_H

static std::unordered_map<SDL_Keycode, int> key_map = {
	{SDLK_x, 0}, {SDLK_1, 1}, {SDLK_2, 2}, {SDLK_3, 3},
	{SDLK_q, 4}, {SDLK_w, 5}, {SDLK_e, 6}, {SDLK_a, 7},
	{SDLK_s, 8}, {SDLK_d, 9}, {SDLK_z, 10}, {SDLK_c, 11},
	{SDLK_4, 12}, {SDLK_r, 13}, {SDLK_f, 14}, {SDLK_v, 15}
};


class Game {
private:
	SDL_Window* window = {};
	SDL_Renderer* renderer = {};
	SDL_Texture* texture = {};
	Chip8 chip8;
	bool quit;
public:
	Game();
	~Game();

	void loadGame(std::string game_name);
	void updateGfx(void const* buffer, int pitch);
	void getKey();
	void run(int delay);
	bool toQuit();

};

#endif // GAME_H