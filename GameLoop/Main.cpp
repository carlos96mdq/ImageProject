#include "Game.h"

int main() {
	
	Game* game = new Game();
	game->init();
	game->loop();
	game->stop();
	delete game;
	
	return 0;
}