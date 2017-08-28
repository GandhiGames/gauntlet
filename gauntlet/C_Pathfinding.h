#pragma once

#include "Component.h"
#include "C_Transform.h"

class C_Pathfinding : public Component
{
	friend class Level;
public:
	C_Pathfinding();
	~C_Pathfinding();

	void Update(float deltaTime) override;

	void Calculate(Level& level, sf::Vector2f target);

	void LoadDependencies(Object* owner);

private:
	sf::Vector2f* GetNextPosition();

	void RemoveFirst();

private:
	sf::Vector2f m_velocity;

	int m_speed;

	std::shared_ptr<C_Transform> m_transform;

	/**
	* The target position of the enemy.
	*/
	std::vector<sf::Vector2f> m_targetPositions;

	/**
	* The current target of the enemy.
	*/
	sf::Vector2f m_currentTarget;
};

