#pragma once
#include "SDL.h"
#include <stdio.h>

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	void checkTile(int &x, int &y);
	bool running();
	bool playerPresent(int &x, int &y);
	void highlightMoveableTiles();
	void initMapEditor();
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

};

