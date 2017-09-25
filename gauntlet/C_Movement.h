#pragma once

#include "C_Transform.h"
#include "C_Updateable.h"

class C_Movement : public Component, public C_Updateable
{
	friend class Object;

public:
	C_Movement(Object* owner);
	~C_Movement();

	void LoadDependencies(Object* owner) override;

	void Update(float timeDelta, Object* owner) override;

	void SetVelocity(const sf::Vector2f& velocity);
	const sf::Vector2f& GetVelocity() const;

private:
	std::shared_ptr<C_Transform> m_transform;

	sf::Vector2f m_velocity;
};

