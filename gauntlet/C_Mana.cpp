#include "PCH.h"
#include "C_Mana.h"


C_Mana::C_Mana(Object* owner) : Component(owner, true),
m_manaDelta(0.f)
{
}


C_Mana::~C_Mana()
{
}

void C_Mana::Update(float deltaTime, Object* owner)
{
	if ((m_manaDelta += deltaTime) > 0.20)
	{
		if (m_current < m_max)
		{
			++m_current;
		}

		m_manaDelta = 0.f;
	}
}


void C_Mana::SetCurrent(const int& current)
{
	m_current = current;

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
