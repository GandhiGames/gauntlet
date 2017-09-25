#pragma once

#include "Component.h"
#include "C_Collidable.h"
#include "C_PointsOnPickup.h"
#include "C_Inventory.h"

//TODO: this and C_Gold are almost identical. Find a way to remove the need for seperate classes.
class C_Gem : public Component, public C_Collidable
{
	friend class Object;
	
public:
	C_Gem(Object* owner);
	~C_Gem();

	void LoadDependencies(Object* owner) override;

	void OnCollisionEnter(Object* owner, Object* other) override;

private:
	std::shared_ptr<C_PointsOnPickup> m_points;
};

