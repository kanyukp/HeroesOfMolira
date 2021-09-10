#include "SDL.h"
#include "Game.h"
#include "titleScreen.h"

Game* game = nullptr;
TitleScreen* title = nullptr;
/*Screen Size Constants*/
const int SCR_WIDTH = 1280;
const int SCR_HEIGHT = 720;

int main(int argc, char* argv[]) {
	/*
	title = new TitleScreen();
	title->init("Heroes of Molira", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCR_WIDTH, SCR_HEIGHT, false);
	while (title->running()) {
		title->handleEvents();
		title->update();
		title->render();
	}
	title->clean();
	*/

	game = new Game();
	game->init("Heroes of Molira", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCR_WIDTH,SCR_HEIGHT, false);
	while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();
	}
	game->clean();

	return 0;
}