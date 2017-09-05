#pragma once

#include "Component.h"
#include "C_Updateable.h"

class C_Torch : public Component, public C_Updateable
{
public:
	C_Torch();
	~C_Torch();

	void Update(float timeDelta, Object* owner) override;

private:
	float DistanceBetweenPoints(sf::Vector2f position1, sf::Vector2f position2);

private:
	float m_brightness;
};

