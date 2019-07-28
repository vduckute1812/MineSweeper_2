#include "Object.h"



Object::Object()
{

}

Object::Object(Object *obj)
{
	m_type = obj->m_type;
	m_position = obj->m_position;
	m_size = obj->m_size;
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
	m_position.x = x;
	m_position.y = y;

	m_type = type;
}

void Object::Update()
{

}

Position Object::GetPosition()
{
	return m_position;
}

Type Object::GetType() const
{
	return m_type;
}

void Object::SetSize(Size size)
{
	m_size = size;
}

Size Object::GetSize() const
{
	return m_size;
}

void Object::SetPosition( Position pos )
{
	m_position = pos;
}

bool Object::IsEnable() const
{
	return m_isEnable;
}
