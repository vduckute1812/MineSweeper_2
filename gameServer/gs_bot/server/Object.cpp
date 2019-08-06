#include "stdafx.h"
#include "Object.h"

Object::Object()
{

}

Object::~Object()
{
}

void Object::SetPosition(const Position& pos)
{
	m_position.x = pos.x;
	m_position.y = pos.y;
}

const Position & Object::GetPosition()
{
	return m_position;
}
