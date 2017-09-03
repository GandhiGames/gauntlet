#include "PCH.h"
#include "Item.h"

// Default constructor.
Item::Item() 
{
	//TODO: can this be static?
	AddComponent<C_AnimatedSprite>();
}

void Item::SetType(ITEM type)
{
	m_type = type;
}

ITEM Item::GetType() const
{
	return m_type;
}
