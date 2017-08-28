#include "PCH.h"
#include "C_Mana.h"


C_Mana::C_Mana() : Component(true)
{
}


C_Mana::~C_Mana()
{
}

void C_Mana::SetCurrent(const int& health)
{
	m_current = health;

	if (m_current > m_max)
	{
		m_max = m_current;
	}
}

int C_Mana::GetCurrent() const
{
	return m_current;
}

int C_Mana::GetMax() const
{
	return m_max;
}
