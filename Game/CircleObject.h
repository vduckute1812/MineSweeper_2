#pragma once
#include "Object.h"
class CircleObject: public Object
{
public:
	CircleObject();
	CircleObject(float radious);

	~CircleObject();

	void	SetRadius(float radious);
	float	GetRadius() const;

	virtual bool	CheckCollision(Object* obj) const;

protected:
	float	m_radius;
};

