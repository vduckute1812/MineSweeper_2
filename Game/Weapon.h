#pragma once

enum WeaponType
{
	WEAP_PISTAL,
	WEAP_RIFLE,
	WEAP_GRENADE,
	WEAP_NONE
};

class Weapon
{
public:
	explicit Weapon();
	virtual ~Weapon();

	virtual void Use() = 0;

	WeaponType	GetType() const;
	int			GetNumAvailable() const;
	

	bool		IsAvailable() const;

protected:
	WeaponType	m_type;
	int			m_numVal;
	int			m_bulletSpeed;
	bool		m_isAvailable;
};

