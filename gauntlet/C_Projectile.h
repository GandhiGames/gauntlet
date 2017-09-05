#pragma once

#include "Component.h"
#include "C_Updateable.h"
#include "C_StaticSprite.h"

class C_Projectile : public Component, public C_Updateable
{
	friend class Object;

public:
	C_Projectile();
	~C_Projectile();

	void Initialise(const sf::Vector2f& origin, const sf::Vector2f& target);

	void LoadDependencies(Object* owner) override;

	void Update(float timeDelta, Object* owner) override;

private:
	std::shared_ptr<C_StaticSprite> m_sprite;
	std::shared_ptr<C_Transform> m_transform;

	//TODO: move to seperate component?
	sf::Vector2f m_velocity;
};

