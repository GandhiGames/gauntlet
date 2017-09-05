#include "PCH.h"
#include "C_Health.h"
#include "Object.h"

//TODO: convert to basestat
C_Health::C_Health() : C_Damageable(true),
	m_current(0),
	m_max(0)
{
}

C_Health::~C_Health()
{
}

void C_Health::LoadDependencies(Object* owner)
{
	m_owner = owner;
}

void C_Health::SetCurrent(const int& health)
{
	m_current = health;

	if (m_current > m_max)
	{
		m_max = m_current;
	}
}

void C_Health::DoDamage(const int& damage)
{
	m_current -= damage;

	if (m_current <= 0)
	{
		m_current = 0;

		//TODO: uncomment when fixing.
		//for (auto& f : m_deathListeners) { f(); }

		m_owner->Destroy();
	}
}

void C_Health::PerformActionOnDeath(const Action& action)
{
	//TODO: fix this! Not compiling m_deathListeners
	//m_deathListeners.emplace_back(action);
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
