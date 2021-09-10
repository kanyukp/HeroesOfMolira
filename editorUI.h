#pragma once
#include "Game.h"
#include <vector>
#include "tile.h"
using namespace std;
class EditorUI
{
public:

	EditorUI(SDL_Renderer* renderer, int x, int y);

	int x;
	int y;
	int currPage;
	vector<vector<Tile*>> textures;
	vector<char> texChars;
	SDL_Rect uiR;
	SDL_Renderer* renderer;
	SDL_Surface* uiTileSurface;
	SDL_Texture* uiTileTex;
	//TODO***
	//finish more efficient way to load in textures
	void parseUITextures();
	
	// End todo
	char selectTex(int x, int y);
	void renderUI(int page);
	void loadTextures();

};

