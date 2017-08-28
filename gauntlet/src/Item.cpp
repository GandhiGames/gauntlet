#include "PCH.h"
#include "Item.h"

// Default constructor.
Item::Item() 
{
	AddComponent<C_Sprite>();
}

void Item::SetType(ITEM type)
{
	m_type = type;
}

ITEM Item::GetType() const
{
	return m_type;
}
