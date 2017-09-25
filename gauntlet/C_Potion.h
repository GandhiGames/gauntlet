#pragma once

#include "Component.h"
#include "C_Collidable.h"
#include "C_PotionType.h"
#include "C_PointsOnPickup.h"

class C_Potion : public Component, public C_Collidable
{
	friend class Object;

public:
	C_Potion(Object* owner);
	~C_Potion();

	void LoadDependencies(Object* owner) override;

	void OnCollisionEnter(Object* owner, Object* other) override;

private:
	std::shared_ptr<C_PotionType> m_type;
	std::shared_ptr<C_PointsOnPickup> m_points;
};

