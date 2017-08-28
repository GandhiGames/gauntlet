#pragma once

#include "Component.h"

class C_PointsOnPickup : public Component
{
public:
	C_PointsOnPickup();
	~C_PointsOnPickup();

	void SetValue(const int& pointsValue);
	int GetValue() const;

private:
	int m_value;
};

