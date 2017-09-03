#pragma once

#include <functional>
#include "C_Damageable.h"

typedef std::function<void(void)> Action;

//TODO: add damageable interface
class C_Health : public C_Damageable
{
public:
	C_Health();
	~C_Health();

	void LoadDependencies(Object* owner) override;

	void SetCurrent(const int& health);
	void DoDamage(const int& damage) override;

	
	//TODO: is max health used? should it be?
	//void SetMax(const int& max);

	int GetCurrent() const;
	int GetMax() const;

	bool IsDead() const;

	void PerformActionOnDeath(const Action& action);

private:
	int m_current;
	int m_max;

	//std::vector<Action&> m_deathListeners;

	Object* m_owner;
};

