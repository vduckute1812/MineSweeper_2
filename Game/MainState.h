#pragma once

#include "Player.h"
#include "Map.h"
#include <iostream>
#include <fstream>  

class MainState
{
public:
	MainState();
	~MainState();

	void	Init();
	void	Update();
	void	Render();
	int		Rand(int min, int max);

private:
	Map *map;
};

