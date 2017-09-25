#pragma once

#include "Component.h"
#include "C_Updateable.h"

//TODO: this code is almost identical to health component. Fix it!
class C_Mana : public Component, public C_Updateable
{
	friend class Object;

public:
	C_Mana(Object* owner);
	~C_Mana();

	void Update(float deltaTime, Object* owner) override;

	void SetCurrent(const int& value);

	int GetCurrent() const;
	int GetMax() const;

	bool IsDead() const;

private:
	int m_current;
	int m_max;

	/**
	* The time since the last mana regeneration.
	*/
	float m_manaDelta;
};

