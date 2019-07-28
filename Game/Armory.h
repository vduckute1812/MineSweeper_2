#pragma once
#include <vector>

class Weapon;
class Helmet;
class Armory
{
public:
	Armory();
	~Armory();

private:
	Helmet*					m_helmet;
	std::vector<Weapon*>	m_weapons;
};

