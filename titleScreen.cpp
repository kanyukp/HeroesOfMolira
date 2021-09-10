#include "titleScreen.h"
#include "SDL_image.h"
#include <SDL_mixer.h>
#include <SDL_mixer.h>
#include <iostream>
using namespace std;

SDL_Texture* playerTex1;
Mix_Music* open_theme1 = NULL;
//int mPosx, mPosy;

TitleScreen::TitleScreen()
{
}

TitleScreen::~TitleScreen()
{
}

void TitleScreen::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "Subsystems Initialised..." << endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
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
	}
	else {
		isRunning = false;
	}

	/*Creates Audio Mixer*/
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	/*Opening Theme Load*/
	open_theme1 = Mix_LoadMUS("Audio/sa_theme.wav");

	//Home Screen Init
	SDL_Surface* tmpSurface = IMG_Load("Textures/medieval.jpg");
	playerTex1 = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);


	//Play Theme
	Mix_PlayMusic(open_theme1, -1);

}

void TitleScreen::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	bool a;
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			isRunning = false;
			break;
		case SDLK_a:
			//******************************
			break;
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		//mPosx = event.button.x;
		//mPosy = event.button.y;
		break;
	default:
		break;
	}
}

void TitleScreen::update()
{
	/*
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
	}*/
}

void TitleScreen::render()
{
}

void TitleScreen::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game Closed!" << endl;
}

bool TitleScreen::running()
{
	return this->isRunning;
}
