#pragma once

#include "Component.h"
#include "ItemFactory.h"

class C_ItemType : public Component
{

public:
	C_ItemType(Object* owner);
	~C_ItemType();

	void Set(ITEM type);

	ITEM Get() const;

private:
	ITEM m_type;
};

