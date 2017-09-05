#pragma once

#include "C_Updateable.h"
#include "C_Transform.h"
#include "C_Movement.h"

class C_Pathfinding : public Component, public C_Updateable
{
	friend class Level;
public:
	C_Pathfinding();
	~C_Pathfinding();

	void LoadDependencies(Object* owner) override;

	void Update(float deltaTime, Object* owner) override;

	void Calculate(Level& level, sf::Vector2f target);

private:
	sf::Vector2f* GetNextPosition();

	void RemoveFirst();

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
};

