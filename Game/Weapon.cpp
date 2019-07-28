#include "Weapon.h"



Weapon::Weapon()
{
	m_numVal = 0;
	m_bulletSpeed = 0;
	m_isAvailable = true;
}


Weapon::~Weapon()
{
}

WeaponType Weapon::GetType() const
{
	return m_type;
}

int Weapon::GetNumAvailable() const
{
	return m_numVal;
}

bool Weapon::IsAvailable() const
{
	return m_isAvailable;
}
