#include "Object.h"



Object::Object()
{
	cycle = new Cycle();
}


Object::~Object()
{
	delete cycle;
}

void Object::init(int x, int y)
{

}

void Object::update()
{

}

void Object::set_position(Position *pos)
{
	cycle->m_x = pos->x;
	cycle->m_y = pos->y;
}

Position Object::get_position()
{
	Position m_pos;
	m_pos.x = cycle->m_x;
	m_pos.y = cycle->m_y;
	return m_pos;
}

void Object::SetPosition( Position pos )
{
	cycle->m_x = pos.x;
	cycle->m_y = pos.y;
}

Position Object::GetPosition()
{
	Position m_pos;
	m_pos.x = cycle->m_x;
	m_pos.y = cycle->m_y;
	return m_pos;
}
