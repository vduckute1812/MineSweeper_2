#pragma once

#include "Define.h"

struct  Position
{
	Position() : x(0), y(0) {}
	int x;
	int y;
};

struct Size
{
	Size() : width(0), height(0) {}
	int width;
	int height;
};

enum Type
{
	CHARACTER,
	PISTAL,
	RIFLE,
	GRENADE,
	HELMET,
	BUSH,
	ROCK,
	BULLET,
	NONE
};

class Object
{
public:
	Object();
	Object(Object* obj);
	Object(int x, int y, Type type = NONE);
	~Object();

	void	Init(int x, int y, Type type);
	void	Update();


	void			SetPosition( Position pos );
	Position		GetPosition();

	Type			GetType() const;

	void			SetSize(Size size);

	Size			GetSize() const;

	bool			IsEnable() const;

protected:
	bool			m_isEnable;

	Type			m_type;
	Position		m_position;
	Size			m_size;
};

