#include "PCH.h"
#include "C_PotionType.h"

C_PotionType::C_PotionType(Object* owner) : Component(owner, true)
{
}

C_PotionType::~C_PotionType()
{
}

POTION C_PotionType::Get() const
{
	return m_type;
}
void C_PotionType::Set(POTION type)
{
	m_type = type;
}
