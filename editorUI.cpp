#include "editorUI.h"
#include <fstream>
#include <iostream>
#include <string>
#define TILESIZE 64
#define COLS 3	
#define NUMPGTEX 6
#define NUMPGS 2
using namespace std;
	EditorUI::EditorUI(SDL_Renderer* renderer, int x, int y) 
	{
		this->renderer = renderer;
		this->x = x;
		this->y = y;
		parseUITextures();
		loadTextures();
	}

	void EditorUI::renderUI(int page) 
	{
		this->currPage = page;
		uiR.h = TILESIZE;
		uiR.w = TILESIZE;
		uiR.x = this->x;
		uiR.y = this->y;
		for (int i = 0; i < textures[page].size(); i++)
		{
			textures[page][i]->draw(uiR);
			//SDL_RenderCopy(renderer, textures[page][i], NULL, &uiR );
			uiR.x += TILESIZE;
			if ((i + 1) % COLS == 0 && i != 0)
			{
				uiR.y += TILESIZE;
				uiR.x = this->x;
			}
		}
		uiR.y += TILESIZE;
		/*
		SDL_Surface* tmpSurface;
		SDL_Texture* pageButton;
		tmpSurface = IMG_Load("Textures/PlayButton.png");
		pageButton = SDL_CreateTextureFromSurface(renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);
		SDL_RenderCopy(renderer, pageButton, NULL, &uiR);
		*/
	}
	void EditorUI::loadTextures() 
	{
		vector <Tile *> rowVector;
		for (int i = 0; i < NUMPGS; i++)
		{
			textures.push_back(rowVector);
			for (int j = 0; j < NUMPGTEX; j++)
			{
				textures[i].push_back(new Tile(this->texChars[(j + (i * NUMPGTEX))], renderer, j, i));
			}
		}
	}
	char EditorUI::selectTex(int mPosx, int mPosy) 
	{
		int standardX = mPosx - this->x;
		int standardY = mPosy - this->y;
		standardX = standardX / TILESIZE;
		standardY = standardY / TILESIZE;
		return textures[this->currPage][standardX + (3 * standardY)]->type;
	}
	void EditorUI::parseUITextures()
	{
		ifstream inFile;
		inFile.open("Textures/texturelist.txt");
		string line;
		int counter = 0;

		while (getline(inFile, line))
		{
			for (int i = 0; i < line.length(); i++) {
				this->texChars.push_back(line[i]);
			}
		}
		inFile.close();
	}