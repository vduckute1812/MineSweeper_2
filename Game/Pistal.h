#pragma once
#include "Weapon.h"
class Pistal: public Weapon
{
public:
	explicit Pistal();
	~Pistal();

	virtual void	Use();

private:
	int		m_rofSpeed;
	bool	m_isAvailable;
};

