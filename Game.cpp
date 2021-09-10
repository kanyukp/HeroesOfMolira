#include "Game.h"
#include "tile.h"
#include <iostream>
#include "SDL_image.h"
#include <SDL_mixer.h>
#include "map.h"
#include "editorUI.h"
#include "character.h"
#include <map>
#include <utility>
#define TILESIZE 64
#define BTTNW 128
#define BTTNH 64
#define GRASS 'g'
#define DIRT 'd'
#define WATER 'w'
#define STONE 's'
#define EMPTY ' '

using namespace std;

int cameraOffsetX = 0;
int cameraOffsetY = 0;

SDL_Texture* playerTex;
SDL_Texture* playButton;
SDL_Texture* mapButton;
SDL_Texture* texSelect;
SDL_Texture* texSelect2;
SDL_Rect srcR, mouR, movR, playR, mapeR, texR, texR2;
SDL_Rect home_screen = { 0, 0, 1280, 720};
bool mainMenu = true;
Map* currMap;
Tile* currTile;
Tile* playerTile;
map <pair<int , int> , Tile*> moveTiles;
int currMousex;
int currMousey;
bool playerMoving = false;
int currMove;
bool titleScreen = true;
bool mapEditor = false;
char selectedTex = 'g';

//Audio Files
Mix_Music* open_theme = NULL;

Map* map1;
Map* levelEditor;
EditorUI* texMenu;
Character* player1;

int x, mPosx = 0;
int y, mPosy = 0;
int menuPage = 0;

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) 
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "Subsystems Initialised..." << endl;
		window = SDL_CreateWindow(title, xpos, ypos, 832/*width*/, 832/*height*/ , flags);
		if (window)
		{
			cout << "window created!" << endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			cout << "renderer created!" << endl;
		}
		isRunning = true;
	} else {
		isRunning = false;
	}

	/*Creates Audio Mixer*/
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	/*Opening Theme Load*/
	open_theme = Mix_LoadMUS("Audio/sa_theme.wav");

	//Home Screen Init
	SDL_Surface* tmpSurface = IMG_Load("Textures/medieval.jpg");
	playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	tmpSurface = IMG_Load("Textures/LevelButton.png");
	mapButton = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	tmpSurface = IMG_Load("Textures/PlayButton.png");
	playButton = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	tmpSurface = IMG_Load("grass1.png");
	texSelect = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	tmpSurface = IMG_Load("dirt1.png");
	texSelect2 = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	//Play Theme
	Mix_PlayMusic(open_theme, -1);
	
	map1 = new Map("Maps/map1.txt", renderer);
	currMap = map1;
	player1 = new Character(renderer);
	map1->boardTile[1][3]->ocCharUpdate(player1);
	
	movR.h = TILESIZE;
	movR.w = TILESIZE;

}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	bool a;
	switch(event.type){
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				isRunning = false;
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				cameraOffsetY += TILESIZE;
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				cameraOffsetY -= TILESIZE;
			}
			else if (event.key.keysym.sym == SDLK_LEFT)
			{
				cameraOffsetX += TILESIZE;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				cameraOffsetX -= TILESIZE;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			mPosx = event.button.x;
			mPosy = event.button.y;
			if (!titleScreen && !levelEditor) {
				if (playerMoving)
				{

				}
				if (playerPresent(mPosx, mPosy))
				{
					currMove = currTile->occChar->moveSpeed;
					playerTile = currTile; //******************************************************

					if (playerMoving)
					{
						playerMoving = false;
					}
					else
					{
						playerMoving = true;
					}
				}
			}
			else if (levelEditor) 
			{
				/*
				if (mPosx >= texR.x && mPosx <= texR.x + TILESIZE && mPosy >= texR.y && mPosy <= texR.y + TILESIZE)
				{
					selectedTex = GRASS;
				}
				else if (mPosx >= texR2.x && mPosx <= texR2.x + TILESIZE && mPosy >= texR2.y && mPosy <= texR2.y + TILESIZE)
				{
					selectedTex = DIRT;
				} */
				if (mPosx > (currMap->width * TILESIZE) && mPosx < (currMap->width * TILESIZE + BTTNW) && mPosy > texMenu->uiR.y && mPosy < texMenu->uiR.y + BTTNH)
				{
					menuPage = 1;
				}
				else if ( mPosx > currMap->width* TILESIZE)
				{
					selectedTex = texMenu->selectTex(mPosx, mPosy);
				}
				else if(mPosx >= 0 && mPosx <= currMap->width * TILESIZE && mPosy >= 0 && mPosy <= currMap->height * TILESIZE)
				{
					checkTile(mPosx, mPosy);
					currTile = currMap->boardTile[mPosy / TILESIZE][mPosx / TILESIZE];
					currTile->type = selectedTex;
					currTile->loadTex(renderer);
				}
			} 
			else 
			{
				if ( mPosx >= playR.x && mPosx <= playR.x + BTTNW && mPosy >= playR.y && mPosy <= playR.y + BTTNH)
				{
					titleScreen = false;
				}
				else if (mPosx >= mapeR.x && mPosx <= mapeR.x + BTTNW && mPosy >= mapeR.y && mPosy <= mapeR.y + BTTNH)
				{
					titleScreen = false;
					mapEditor = true;
					initMapEditor();
				}
				else 
				{
				}
			}
			break;
		default:
			break;
	}
}

void Game::update()
{
	//x += 1;
	SDL_PumpEvents();
	SDL_GetMouseState(&currMousex, &currMousey);
	if (currMousex > 0) {
		
			checkTile(currMousex, currMousey);
			mouR.h = TILESIZE;
			mouR.w = TILESIZE;
			mouR.x = currMousex;
			mouR.y = currMousey;
			//currTile = currMap->boardTile[currMousey/TILESIZE][currMousex/TILESIZE];
	}

}

void Game::render()
{
	SDL_RenderClear(renderer);
	//THIS IS WHERE YOU ADD THINGS TO RENDER

	if (!titleScreen && !mapEditor) {
		map1->draw(cameraOffsetX, cameraOffsetY);
		auto it = moveTiles.find(make_pair((mouR.x -cameraOffsetX) / TILESIZE, (mouR.y - cameraOffsetY) / TILESIZE));
		if (playerMoving)
		{
			if (it != moveTiles.end()) {

				SDL_RenderDrawLine(renderer, (currTile->yPos * TILESIZE )+ cameraOffsetX + 32, (currTile->xPos * TILESIZE) + cameraOffsetY + 32, mouR.x + 32, mouR.y + 32);
			}
		}
		else
		{
			SDL_RenderDrawRect(renderer, &mouR);
		}
		if (playerMoving && currTile->occChar == player1)
		{
			highlightMoveableTiles();
		}
		else if (playerMoving && it != moveTiles.end())
		{
			playerMoving = false;
			it->second->ocCharUpdate(player1);
			it->second->occupied = true;
			playerTile->ocCharUpdate(nullptr);
			playerTile->occupied = false;
		}
		else {
			playerMoving = false;
		}
	}
	else if (mapEditor) 
	{
		levelEditor->draw(cameraOffsetX, cameraOffsetY);
		texMenu->renderUI(menuPage);
		/*
		texR.h = TILESIZE;
		texR.w = TILESIZE;
		texR.x = (levelEditor->width * TILESIZE) + 20;
		texR.y = 450;

		SDL_RenderCopy(renderer, texSelect, NULL, &texR);
		texR2.h = TILESIZE;
		texR2.w = TILESIZE;
		texR2.x = (levelEditor->width * TILESIZE) + 20;
		texR2.y = 514;
		SDL_RenderCopy(renderer, texSelect2, NULL, &texR2);
		*/
	}
	else
	{
		SDL_RenderCopy(renderer, playerTex, NULL, &home_screen);
		mapeR.h = BTTNH;
		mapeR.w = BTTNW;
		mapeR.x = 250;
		mapeR.y = 450;

		playR.h = BTTNH;
		playR.w = BTTNW;
		playR.x = 450;
		playR.y = 450;

		SDL_RenderCopy(renderer, mapButton, NULL, &mapeR);
		SDL_RenderCopy(renderer, playButton, NULL, &playR);

		playerMoving = false;
	}
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game Closed!" << endl;
}
bool Game::running() {
	return this->isRunning;
}
void Game::checkTile(int &x, int &y) {
	if ( x < (currMap->width * TILESIZE) && y < (currMap->height * TILESIZE)) {
		y = (((y / TILESIZE)) * TILESIZE);
		x = (((x / TILESIZE)) * TILESIZE);
	}
	//currTile = currMap->boardTile[y / TILESIZE][x / TILESIZE];
}
bool Game::playerPresent(int& x, int& y) {
	checkTile(x, y);
	currTile = currMap->boardTile[(y / TILESIZE) + (-cameraOffsetY/ TILESIZE)][x / TILESIZE + (-cameraOffsetX / TILESIZE)];
	if (currTile->occupied) {
		return true;
	}
	else {
		return false;
	}
}
void Game::highlightMoveableTiles() {
	int xpos = currTile->xPos;
	int ypos = currTile->yPos;
	movR.x = xpos * TILESIZE;
	movR.y = ypos * TILESIZE;
	int counter = 0;
	moveTiles.clear();
	/*
	HOLY FUCK THIS WAS MAXIMUM AIDS
	*/
	for (int i = xpos - currMove; i <= currMove + xpos; i++)
	{
		if ( i >= currMap->height || i < 0)
		{
			if ( i < xpos) {
				counter++;
			}
			else {
				counter--;
			}
			//movR.x += TILESIZE;
			continue;
		}
		movR.x = i * TILESIZE;
		for (int j = ypos - counter; j <= ypos + counter; j++)
		{
			if (j >= currMap->width || j < 0)
			{
				continue;
			}
			moveTiles.emplace(make_pair(j, i), currMap->boardTile[i][j]);
			movR.x = j * TILESIZE + (cameraOffsetX);
			movR.y = i * TILESIZE + (cameraOffsetY);
			SDL_RenderDrawRect(renderer, &movR);
		}
		if (i < xpos) {
			counter++;
		}
		else {
			counter--;
		}
	}
}
void Game::initMapEditor() {
	levelEditor = new Map(renderer, 10);
	currMap = levelEditor;
	texMenu = new EditorUI(renderer, 640, 0);
	mapEditor = true;
}

