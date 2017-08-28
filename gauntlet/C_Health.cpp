#include "PCH.h"
#include "C_Health.h"

//TODO: convert to basestat
C_Health::C_Health() : Component(true),
	m_current(0),
	m_max(0)
{
}

C_Health::~C_Health()
{
}

void C_Health::SetCurrent(const int& health)
{
	m_current = health;

	if (m_current > m_max)
	{
		m_max = m_current;
	}
}

void C_Health::Damage(const int& damage)
{
	m_current -= damage;

	if (m_current < 0)
	{
		m_current = 0;
	}
}

/*
void C_Health::SetMax(const int& max)
{
	m_max = max;

	if (m_current > m_max)
	{
		m_current = m_max;
	}
}
*/

int C_Health::GetCurrent() const
{
	return m_current;
}

int C_Health::GetMax() const
{
	return m_max;
}

bool C_Health::IsDead() const
{
	return m_current <= 0;
}
