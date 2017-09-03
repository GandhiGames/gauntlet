#pragma once

#include "Component.h"

enum class POTION {
	ATTACK,
	DEFENSE,
	STRENGTH,
	DEXTERITY,
	STAMINA,
	COUNT
};

//TODO: convert to C_Tag.
class C_PotionType : public Component
{
public:
	C_PotionType();
	~C_PotionType();

	POTION Get() const;
	void Set(POTION type);

private:
	POTION m_type;
};

