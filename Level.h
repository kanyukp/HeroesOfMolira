#pragma once
#include "SDL.h"
#include "map.h"
#include <stdio.h>


class Level
{
public:
	Level(string file);
	~Level();

	string levelData;
	string levelID;
	Map* levelMap;
	int enemyCount;
	vector<vector<char>> levelInfo;
	
	void parse(string file);

private:

};

