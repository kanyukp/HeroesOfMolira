#pragma once
#include "Game.h"
#include "SDL_image.h"
class Character
{

public:
	Character(SDL_Renderer* renderer);
	~Character();
	int x;
	int y;
	int health;
	int moveSpeed;
	SDL_Renderer* renderer;
	SDL_Surface* playerSurface;
	SDL_Texture* playerTex;
	void draw(int x, int y);
	void loadTex(SDL_Renderer* renderer);
};

