#include "Rectangle.h"

Rectangle::Rectangle()
{
	m_x = 0;
	m_y = 0;
	m_width = 0;
	m_heigh = 0;
}


Rectangle::~Rectangle()
{
	m_x = 0;
	m_y = 0;
	m_width = 0;
	m_heigh = 0;
}

void Rectangle::Init( int x, int y )
{
	m_width = x;
	m_heigh = y;
}

int Rectangle::GetWidth()
{
	return m_width;
}

int Rectangle::GetHeigh()
{
	return m_heigh;
}
