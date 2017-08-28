#include "PCH.h"
#include "C_PointsOnPickup.h"


C_PointsOnPickup::C_PointsOnPickup() : Component(true),
	m_value(0)
{
}


C_PointsOnPickup::~C_PointsOnPickup()
{
}

int C_PointsOnPickup::GetValue() const
{
	return m_value;
}

void C_PointsOnPickup::SetValue(const int& pointsValue)
{
	m_value = pointsValue;
}
