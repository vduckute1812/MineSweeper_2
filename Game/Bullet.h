#pragma once
#include "Object.h"


enum BulletType
{
	PISTAL_BULLET,
	RIFLE_BULLET,
	GRENADE_BULLET,		// not a bullet but can set here like a special bullet
	NONE_BULLET
};

class Bullet: public Object
{
public:
	Bullet();
	virtual ~Bullet();

protected:
	BulletType	m_type;
	float		m_directAngle;
};
