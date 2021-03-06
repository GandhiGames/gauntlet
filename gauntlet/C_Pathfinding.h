#pragma once

#include "C_Updateable.h"
#include "C_Transform.h"
#include "C_Movement.h"

class C_Pathfinding : public Component, public C_Updateable
{
	friend class Level;
	friend struct Tile;
public:
	C_Pathfinding(Object* owner);
	~C_Pathfinding();

	void LoadDependencies(Object* owner) override;

	void Update(float deltaTime, Object* owner) override;

private:
	//TODO: moved to fixed time step, no need to calculate every update!
	void Calculate(Level* level, const sf::Vector2f& target);

	sf::Vector2f* GetNextPosition();

	void RemoveFirst();

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
	std::shared_ptr<C_Transform> m_transform;

	std::shared_ptr<C_Movement> m_movement;
	/**
	* The target position of the enemy.
	*/
	std::vector<sf::Vector2f> m_targetPositions;

	/**
	* The current target of the enemy.
	*/
	sf::Vector2f m_currentTarget;

	int m_speed;

	Tile* m_prevTargetTile;
};

