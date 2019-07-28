#include "Rifle.h"

Rifle::Rifle()
{
	m_type = WEAP_RIFLE;
}


Rifle::~Rifle()
{
}

void Rifle::Use()
{
	m_numVal--;
}
