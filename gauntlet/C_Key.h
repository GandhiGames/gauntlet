#pragma once
#include "Component.h"
#include "C_Collidable.h"

class C_Key : public Component, public C_Collidable
{
	friend class Object;

public:
	C_Key(Object* owner);
	~C_Key();

	void OnCollisionEnter(Object* owner, Object* other) override;
};

