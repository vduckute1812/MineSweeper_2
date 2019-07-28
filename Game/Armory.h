#pragma once
#include <vector>

class Weapon;
class Helmet;
enum WeaponType;
class Armory
{
public:
	Armory();
	~Armory();

	void		Init();

	void		SetWeapon(WeaponType type);
	void		UseWeapon();

	Weapon*		GetCurrentWeapon() const;
	WeaponType	GetCurrentWeaponType() const;
	int			GetWeaponAvailable(WeaponType type);

private:
	Weapon*					m_currentWeapon;
	Helmet*					m_helmet;
	std::vector<Weapon*>	m_weapons;
};

