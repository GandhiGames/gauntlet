#pragma once

#include "Component.h"

//TODO: add damageable interface
class C_Health : public Component
{
public:
	C_Health();
	~C_Health();

	void SetCurrent(const int& health);
	void Damage(const int& damage);
	
	//TODO: is max health used? should it be?
	//void SetMax(const int& max);

	int GetCurrent() const;
	int GetMax() const;

	bool IsDead() const;

private:
	int m_current;
	int m_max;
};

