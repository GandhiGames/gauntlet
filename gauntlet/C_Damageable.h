#pragma once

#include "Component.h"

//TODO: delete cpp.
//TODO: actually implement. All classes that get health should now get all damagables.
class C_Damageable : public Component
{
public:
	C_Damageable(bool requiresUnique);
	~C_Damageable();

	//TODO: add damage direction
	virtual void DoDamage(const int& damage) = 0;
};

