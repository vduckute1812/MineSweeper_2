#pragma once
#include "Weapon.h"
class Grenade: public Weapon
{
public:
	explicit Grenade();
	~Grenade();

	virtual void Use();
};

