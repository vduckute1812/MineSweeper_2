#include "Weapon.h"



Weapon::Weapon()
{
	m_numVal = 0;
	m_bulletSpeed = 0;
}


Weapon::~Weapon()
{
}

WeaponType Weapon::GetType() const
{
	return m_type;
}
