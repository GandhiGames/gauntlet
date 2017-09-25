#include "PCH.h"
#include "C_ItemType.h"


C_ItemType::C_ItemType(Object* owner) : Component(owner, true), m_type(ITEM::COUNT)
{
}


C_ItemType::~C_ItemType()
{
}

void C_ItemType::Set(ITEM type)
{
	m_type = type;
}

ITEM C_ItemType::Get() const
{
	return m_type;
}

