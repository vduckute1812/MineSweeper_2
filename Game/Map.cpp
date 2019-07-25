#include "Map.h"

Map *Map::m_instance = nullptr;

Map* Map::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new Map();
	}
	return m_instance;
}

void Map::Destroy()
{
	if (m_instance)
	{
		delete m_instance;
	}
}


Map::Map()
{
	/*if( m_instance == NULL )
	{
		m_instance = new Map();
	}*/
}

Map::Map( int width, int height )
{
	m_rec.Init( width, height );
}


Map::~Map()
{
}

int Map::GetWidth()
{
	return m_rec.GetWidth();
}
int Map::GetHeigh()
{
	return m_rec.GetHeigh();
}
