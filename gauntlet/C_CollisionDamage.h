#pragma once

#include "C_Updateable.h"
#include "C_Transform.h"

class C_CollisionDamage : public Component, public C_Updateable
{
public:
	C_CollisionDamage();
	~C_CollisionDamage();

	void LoadDependencies(Object* owner) override;

	void Update(float deltaTime, Object* owner) override;

	void SetDamageAmount(int amount);
	void SetTargetTag(std::string tag);
	void SetSoundOnHit(sf::Sound* collisionSound);

	//TODO: is having vector2.zero the best default option? should it be the sound listeners location?
	void PlaySound(sf::Sound* sound, sf::Vector2f position = { 0.f, 0.f });


private:
	int m_damageAmount;
	std::string m_targetTag;
	std::shared_ptr<C_Transform> m_transform;
	sf::Sound* m_collisionSound;
};

