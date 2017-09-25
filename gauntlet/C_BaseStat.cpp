#include "PCH.h"
#include "C_BaseStat.h"

//TODO: Is subclassing this for each stat the right thing to do?
C_BaseStat::C_BaseStat(Object* owner) : Component(owner, true),
	m_value(0)
{
}

int C_BaseStat::GetValue() const
{
	return m_value;
}

void C_BaseStat::SetValue(int value)
{
	m_value = value;
}
