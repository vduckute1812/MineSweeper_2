#pragma once

#include <vector>
#include "Define.h"
#include "Rectangle.h"
#include "Cycle.h"

class Map
{
public:
	static Map *GetInstance();
	static void Destroy();
	Map();
	Map(int width, int height);
	~Map();
	int GetWidth();
	int GetHeigh();
private:
	static Map *m_instance;

	Rectangle m_rec;
	Cycle m_cycle;
};

