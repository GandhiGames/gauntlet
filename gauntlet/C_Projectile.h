#pragma once

#include "Component.h"
#include "C_Updateable.h"
#include "C_Collidable.h"
#include "C_StaticSprite.h"

class C_Projectile : public Component, public C_Updateable, public C_Collidable
{
	friend class Object;

public:
	C_Projectile(Object* owner);
	~C_Projectile();

	void Initialise(const sf::Vector2f& origin, const sf::Vector2f& target, const int& damageAmount, const std::string& targetTag);

	void LoadDependencies(Object* owner) override;

	void OnCollisionEnter(Object* owner, Object* other) override;

	void Update(float timeDelta, Object* owner) override;

	void SetSoundOnHit(sf::Sound* collisionSound);

	const std::string& GetTargetTag() const;
	const int& GetDamageAmount() const;

private:
	std::shared_ptr<C_StaticSprite> m_sprite;
	std::shared_ptr<C_Transform> m_transform;

	//TODO: move to seperate component?
	sf::Vector2f m_velocity;

	int m_damageAmount;
	std::string m_targetTag;
	sf::Sound* m_collisionSound;
};

