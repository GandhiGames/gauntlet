#include "PCH.h"
#include "C_Inventory.h"


C_Inventory::C_Inventory(Object* owner) : Component(owner, true),
m_gold(0), m_score(0) //, m_keys(0)
{
}


C_Inventory::~C_Inventory()
{
}
