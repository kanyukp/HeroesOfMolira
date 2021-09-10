#include "map.h"
#include <string>
#include <iostream>
#include <fstream>
#define TILESIZE 64
using namespace std;
SDL_Rect destR;
Map::Map(string file, SDL_Renderer* renderer) {
	this->filename = file;
	this->renderer = renderer;
	parse(filename);
	populateTiles();
}
Map::Map(SDL_Renderer* renderer, int size) {
	this->renderer = renderer;
	populateMapEditor(size);
}
void Map::parse(string file) {

	ifstream inFile;
	inFile.open(this->filename);
	string line;
	int counter = 0;
	vector <char> rowVector;
	while (getline(inFile, line)) 
	{	
		this->board.push_back(rowVector);
		for (int i = 0; i < line.length(); i++) {
			this->board[counter].push_back(line[i]);
		}
		counter++;
	}
	inFile.close();

}
void Map::populateTiles() {
	vector <Tile *> rowVector;
	for (int i = 0; i < this->board.size(); i++) {
		this->boardTile.push_back(rowVector);
		for (int j = 0; j < this->board[0].size(); j++) {
			this->boardTile[i].push_back(new Tile(this->board[i][j], this->renderer));
			this->boardTile[i][j]->xPos = i;
			this->boardTile[i][j]->yPos = j;
		}
	}
	this->height = boardTile.size();
	this->width = boardTile[0].size();
	//cout << this->width << endl;
}

void Map::draw(int offsetx, int offsety) {
	destR.h = TILESIZE;
	destR.w = TILESIZE;
	for (int i = 0; i < this->boardTile.size(); i++) {
		for (int j = 0; j < this->boardTile[0].size(); j++) {
			destR.x = j * TILESIZE + offsetx;
			destR.y = i * TILESIZE + offsety;
			this->boardTile[i][j]->draw(destR);
			//SDL_RenderCopy(this->renderer, this->boardTile[i][j]->tileTex, NULL, &destR);
		}
	}
}
void Map::populateMapEditor(int size) {
	vector <Tile*> rowVector;
	char empty = ' ';
	for (int i = 0; i < size; i++) {
		this->boardTile.push_back(rowVector);
		for (int j = 0; j < size; j++) {
			this->boardTile[i].push_back(new Tile(empty, this->renderer));
			this->boardTile[i][j]->xPos = i;
			this->boardTile[i][j]->yPos = j;
		}
	}
	this->height = boardTile.size();
	this->width = boardTile[0].size();
}
