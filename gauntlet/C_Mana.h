#pragma once

#include "Component.h"

//TODO: this code is almost identical to health component. Fix it!
class C_Mana : public Component
{
public:
	C_Mana();
	~C_Mana();

	void SetCurrent(const int& value);

	int GetCurrent() const;
	int GetMax() const;

	bool IsDead() const;

private:
	int m_current;
	int m_max;
};

