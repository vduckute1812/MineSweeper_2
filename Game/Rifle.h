#pragma once
#include "Weapon.h"
class Rifle: public Weapon
{
public:
	explicit Rifle();
	~Rifle();

	virtual void Use();
};

