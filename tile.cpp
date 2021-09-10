#include "tile.h"
#include "SDL_image.h"
#define GRASS 'g'
#define DIRT 'd'
#define WATER 'w'
#define STONE 's'
#define EMPTY ' '


Tile::Tile(char type, SDL_Renderer* renderer)
{
	this->type = type;
	this->renderer = renderer;
	loadTex(renderer);
}
Tile::Tile(char type, SDL_Renderer* renderer, int x, int y)
{
	this->type = type;
	this->renderer = renderer;
	loadTex(renderer);
	this->xPos = x;
	this->yPos = y;
}

Tile::~Tile() 
{

}

void Tile::draw(SDL_Rect destR) {

	SDL_RenderCopy(this->renderer, this->tileTex, NULL, &destR);
	if (this->occupied == true) {
		this->occChar->draw(destR.x, destR.y);
	}
}
void Tile::loadTex(SDL_Renderer* renderer) {
	switch (this->type) {
	case GRASS:
		this->tileSurface = IMG_Load("grass1.png");
		this->tileTex = SDL_CreateTextureFromSurface(renderer, tileSurface);
		break;
	case DIRT:
		this->tileSurface = IMG_Load("dirt1.png");
		this->tileTex = SDL_CreateTextureFromSurface(renderer, tileSurface);
		break;
	case WATER:
		this->tileSurface = IMG_Load("water1.png");
		this->tileTex = SDL_CreateTextureFromSurface(renderer, tileSurface);
		break;
	case STONE:
		this->tileSurface = IMG_Load("rock1.png");
		this->tileTex = SDL_CreateTextureFromSurface(renderer, tileSurface);
		break;
	case EMPTY:
		this->tileSurface = IMG_Load("Textures/emptySquare.png");
		this->tileTex = SDL_CreateTextureFromSurface(renderer, tileSurface);
		break;
	}
	SDL_FreeSurface(this->tileSurface);
}
void Tile::ocCharUpdate(Character* occChar) {
	this->occupied = true;
	this->occChar = occChar;
}