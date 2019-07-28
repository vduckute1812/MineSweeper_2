#pragma once
#include "Weapon.h"
class Mine: public Weapon
{
public:
	explicit Mine();
	~Mine();

	virtual void Use();
};

