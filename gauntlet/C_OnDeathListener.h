#pragma once

#include "Component.h"

//TODO: rename - remove C_
class C_OnDeathListener : public Component
{
public:
	C_OnDeathListener(Object* owner, bool requiresUnique) : Component(owner, requiresUnique) {};
	virtual ~C_OnDeathListener() = 0;

	virtual void OnDeath(Object* owner) {};
};

