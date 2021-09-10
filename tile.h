#pragma once
#include "SDL.h"
#include "character.h"

class Tile 
{
public:
	Tile(char type, SDL_Renderer* renderer);
	Tile(char type, SDL_Renderer* renderer, int x, int y);
	~Tile();

	char type;
	bool occupied;
	int xPos;
	int yPos;
	SDL_Renderer* renderer;
	Character* occChar;
	SDL_Surface* tileSurface;
	SDL_Texture* tileTex;
	void draw(SDL_Rect destR);
	void loadTex(SDL_Renderer* renderer);
	void ocCharUpdate(Character* occChar);
};

