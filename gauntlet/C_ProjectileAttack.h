#pragma once

#include "C_Updateable.h"
#include "C_Drawable.h"
#include "C_Transform.h"
#include "C_Mana.h"

class C_ProjectileAttack : public Component, public C_Updateable
{
	friend class SharedContext;
	friend class Projectile;
public:
	C_ProjectileAttack(Object* owner);
	~C_ProjectileAttack();
	
	void LoadDependencies(Object* owner) override;

	void Update(float deltaTime, Object* owner) override;

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
};

