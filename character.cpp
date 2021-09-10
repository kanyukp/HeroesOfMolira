#include "character.h"
SDL_Rect destPR;
Character::Character(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	loadTex(renderer);
	this->moveSpeed = 3;
}
Character::~Character()
{}
void Character::loadTex(SDL_Renderer* renderer) {

		this->playerSurface = IMG_Load("player2.png");
		this->playerTex = SDL_CreateTextureFromSurface(renderer, playerSurface);
		SDL_FreeSurface(this->playerSurface);
}
void Character::draw(int x, int y) {
	destPR.h = 64;
	destPR.w = 64;
	destPR.x = x;
	destPR.y = y;
	SDL_RenderCopy(this->renderer, this->playerTex, NULL, &destPR);
}