#pragma once

#include "Component.h"
#include "C_Collidable.h"
#include "C_PointsOnPickup.h"

class C_Heart : public Component, public C_Collidable
{
	friend class Object;

public:
	C_Heart(Object* owner);
	~C_Heart();

	void LoadDependencies(Object* owner) override;

	void OnCollisionEnter(Object* owner, Object* other) override;

private:
	std::shared_ptr<C_PointsOnPickup> m_healthToAdd;
};

