#pragma once

enum WeaponType
{
	PISTAL_WEAP,
	RIFLE_WEAP,
	GRENADE_WEAP,
	NONE_WEAP
};

class Weapon
{
public:
	explicit Weapon();
	virtual ~Weapon();

	WeaponType GetType() const;

protected:
	WeaponType	m_type;
	int			m_numVal;
	int			m_bulletSpeed;
};

