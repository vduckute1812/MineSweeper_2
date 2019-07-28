#include "Pistal.h"



Pistal::Pistal()
{
	m_type = WEAP_PISTAL;
}


Pistal::~Pistal()
{
}

void Pistal::Use()
{
	m_numVal--;
}

