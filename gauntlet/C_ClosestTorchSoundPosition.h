#pragma once

#include "Component.h"
#include "C_Updateable.h"

class C_ClosestTorchSoundPosition : public Component, public C_Updateable
{
	friend class Object;
public:
	C_ClosestTorchSoundPosition(Object* owner);
	~C_ClosestTorchSoundPosition();

	void Update(float deltaTime, Object* owner) override;

private:

	//TODO: move to Util class
	/**
	* Calculates the distance between two points
	* @param position1 The position of the first point.
	* @param position2 The position of the second item.
	* @return The distance between the two points.
	*/
	float DistanceBetweenPoints(const sf::Vector2f& position1, const sf::Vector2f& position2)
	{
		return (abs(sqrt(((position1.x - position2.x) * (position1.x - position2.x)) + ((position1.y - position2.y) * (position1.y - position2.y)))));
	}

private:
	sf::Sound m_fireSound;
};

