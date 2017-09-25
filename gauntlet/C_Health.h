#pragma once

#include <functional>
#include "Component.h"
#include "C_Collidable.h"

//TODO: add damageable interface
class C_Health : public Component, public C_Collidable
{
public:
	C_Health(Object* owner);
	~C_Health();

	void OnCollisionEnter(Object* owner, Object* other) override;

	void SetCurrent(const int& health);
	void DoDamage(const int& damage, Object* owner);


	//TODO: is max health used? should it be?
	void SetMax(const int& max);

	int GetCurrent() const;
	int GetMax() const;

	bool IsDead() const;

private:
	int m_current;
	int m_max;
};

