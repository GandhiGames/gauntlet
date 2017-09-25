#pragma once

#include "Component.h"
#include "C_Updateable.h"
#include "Util.h"

//TODO: can this be merged with C_Torch. Can lead to confusion having two seperate torch components. What is the difference really?
class C_PlayerTorch : public Component, public C_Updateable
{
	friend class Object;

public:
	C_PlayerTorch(Object* owner);
	~C_PlayerTorch();

	void Update(float timeDelta, Object* owner) override;

private:
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

