#pragma once
#include "Weapon.h"
class Pistal: public Weapon
{
public:
	explicit Pistal();
	virtual ~Pistal();

private:
	int m_rofSpeed;
};

