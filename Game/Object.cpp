#include "Object.h"



Object::Object()
{

}

Object::Object(Object *obj)
{
	m_type = obj->m_type;
	m_position = obj->m_position;
}

Object::Object(int x, int y, Type type)
{
	m_type = type;
	m_position.x = x;
	m_position.y = y;
}

Object::~Object()
{

}

void Object::Init(int x, int y, Type type)
{
	m_type = type;
	m_position.x = x;
	m_position.y = y;
}

void Object::Update()
{

}

Position Object::GetPosition()
{
	return m_position;
}

void Object::SetType(Type type)
{
	m_type = type;
}

Type Object::GetType() const
{
	return m_type;
}


void Object::SetPosition( Position pos )
{
	m_position = pos;
}

void Object::SetEnable(bool isEnable)
{
	m_isEnable = isEnable;
}

bool Object::IsEnable() const
{
	return m_isEnable;
}

Shape Object::GetShape() const
{
	return m_shape;
}
