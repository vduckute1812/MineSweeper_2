#pragma once
#include "Object.h"

class RetangleObject: public Object
{
public:
	RetangleObject();
	~RetangleObject();

	void			SetSize(Size size);
	Size			GetSize() const;

	float			GetWidth() const;
	float			GetHeight() const;

	float			GetAngle();

	virtual bool CheckCollision(Object* obj) const;

protected:
	Size			m_size;
	float			m_angle;
};

