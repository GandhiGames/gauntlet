#pragma once

#include "Component.h"
#include "C_Updateable.h"
#include <unordered_set>

class C_DistanceBasedCollision : public Component, public C_Updateable
{
	friend class Object;

public:
	C_DistanceBasedCollision(Object* owner);
	~C_DistanceBasedCollision();

	void Update(float deltaTime, Object* owner) override;

private:
	std::unordered_set<int> m_colliding;

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
};

