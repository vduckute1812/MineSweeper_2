#include "Map.h"



Map::Map()
{
}

Map::Map(int width, int height)
{
	m_width = width;
	m_heigh = height;
}

Map::~Map()
{
}

void Map::Init()
{

}

void Map::SetWidthMap(int width)
{
	m_width = width;
}

int Map::GetWidth()
{
	return m_width;
}

void Map::SetHeightMap(int height)
{
	m_heigh = height;
}

int Map::GetHeigh()
{
	return m_heigh;
}
