#pragma once

#include "Component.h"

class C_Inventory : public Component
{
public:
	C_Inventory(Object* owner);
	~C_Inventory();

	//TODO: create better way to store inventory
	int m_gold;
	int m_score;
	//int m_keys;
};

