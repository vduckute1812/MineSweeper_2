#include "Armory.h"
#include "Pistal.h"
#include "Rifle.h"
#include "Grenade.h"

Armory::Armory()
{
}


Armory::~Armory()
{
}

void Armory::Init()
{
	m_weapons.push_back(new Pistal());
	m_weapons.push_back(new Rifle());
	m_weapons.push_back(new Grenade());
}

void Armory::SetWeapon(WeaponType type)
{
}

void Armory::UseWeapon()
{
	m_currentWeapon->Use();
}

Weapon * Armory::GetCurrentWeapon() const
{
	return m_currentWeapon;
}

WeaponType Armory::GetCurrentWeaponType() const
{
	return m_currentWeapon->GetType();
}

int Armory::GetWeaponAvailable(WeaponType type)
{
	for (Weapon* weapon: m_weapons)
	{
		if (weapon->GetType() == type)
		{
			return weapon->GetNumAvailable();
		}
	}
	return 0;
}
