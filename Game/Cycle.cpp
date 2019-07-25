#include "Cycle.h"

Cycle::Cycle()
{
	m_x = 0;
	m_y = 0;
	m_r = 0;
}


Cycle::~Cycle()
{
	m_x = 0;
	m_y = 0;
	m_r = 0;
}

void Cycle::init(int x, int y, int r)
{
	m_x = x;
	m_y = y;
	m_r = r;
}

void Cycle::update()
{
}
