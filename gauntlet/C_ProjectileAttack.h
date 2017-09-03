#pragma once

#include "C_Transform.h"
#include "C_Mana.h"

class C_ProjectileAttack : public Component
{
	friend class SharedContext;
	friend class Projectile;
public:
	C_ProjectileAttack();
	~C_ProjectileAttack();
	
	void LoadDependencies(Object* owner) override;

	void Update(float deltaTime) override;
	void Draw(sf::RenderWindow &window, float timeDelta) override;

private:
	std::shared_ptr<C_Transform> m_transform;
	std::shared_ptr<C_Mana> m_mana;

	int m_projectileTextureID;

	/**
	* The time since the player's last attack.
	*/
	float m_attackDelta;

	/**
	* Is the player attacking.
	*/
	bool m_isAttacking;

	/**
	* A vector of all the player's projectiles.
	*/
	std::vector<std::unique_ptr<Projectile>> m_playerProjectiles;

	SharedContext* m_context;

	sf::Vector2f m_screenCenter;

};

