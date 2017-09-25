#pragma once

#include "Component.h"

//TODO: move this to C_Gold, C_Gem etc?
class C_PointsOnPickup : public Component
{
public:
	C_PointsOnPickup(Object* owner);
	~C_PointsOnPickup();

	void SetValue(const int& pointsValue);
	int GetValue() const;

private:
	int m_value;
};

