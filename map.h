#pragma once
#include "SDL.h"
#include "tile.h"
#include <vector>
#include <string>
using namespace std;
class Map
{
public:
	Map(string file, SDL_Renderer* renderer);
	Map(SDL_Renderer* renderer, int size);
	~Map();
	
	SDL_Renderer* renderer;
	int x;
	int y;
	int width;
	int height;
	string filename;
	vector<vector<Tile*>> boardTile;
	vector<vector<char>> board;
	void parse(string file);
	void populateTiles();
	void draw(int offsetx, int offsety/*SDL_Renderer* renderer*/);
	void populateMapEditor(int size);

};

