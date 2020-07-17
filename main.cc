#include <iostream>
#include <string>
#include "game.h"

int main(int argc, char* argv[])
{
	if (argc != 3) {
		std::cerr << "Arguments missing!";
		exit(1);
	}
	
	std::string game_name = "games/";
	game_name += argv[1];
	int delay = atoi(argv[2]);


  	Game myGame;
  	myGame.loadGame(game_name);
	myGame.run(delay);

	return 0;
}
