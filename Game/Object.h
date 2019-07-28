#pragma once

#include "Define.h"

struct  Position
{
	Position() : x(0), y(0) {}
	Position(float x_, float y_) : x(x_), y(y_) {}
	float x;
	float y;
};

struct Size
{
	Size() : width(0), height(0) {}
	Size(float w_, float h_) : width(w_), height(h_) {}
	float width;
	float height;
};

struct Direction
{
	Direction() : d_x(0), d_y(0) {}
	Direction(float x_, float y_) : d_x(x_), d_y(y_) {}
	float d_x;
	float d_y;
};

enum Shape
{
	CIRCLE,
	RECTANGLE
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
	virtual ~Object();

	virtual bool CheckCollision(Object* obj) const = 0;

	void	Init(int x, int y, Type type);
	void	Update();

	void			SetPosition( Position pos );
	Position		GetPosition();

	void			SetType(Type type);
	Type			GetType() const;

	void			SetEnable(bool isEnable);
	bool			IsEnable() const;

	Shape			GetShape() const;

protected:
	bool			m_isEnable;

	Shape			m_shape;
	Type			m_type;
	Position		m_position;
};

