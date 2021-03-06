#pragma once

#include "Component.h"
#include "C_Updateable.h"
#include "C_Movement.h"
#include "Input.h"


//TODO: rename to controller? or make work only with keyboard
class C_KeyboardController : public Component, public C_Updateable
{
	friend class Object;
	friend class Level;

public:
	C_KeyboardController(Object* owner);
	~C_KeyboardController();

	void LoadDependencies(Object* owner) override;

	void Update(float timeDelta, Object* owner) override;

private:
	//TODO: should keyboard controller care about collisions? what if we want to change how collisions are checked?
	bool CausesCollision(const sf::Vector2f& movement, Level& level);

private:
	std::shared_ptr<C_Movement> m_movement;
	std::shared_ptr<C_Transform> m_transform;

	//TODO: should keyboard controller decide movement speed? probably not.
	int m_speed;
};

