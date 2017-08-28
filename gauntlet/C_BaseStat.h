#pragma once

#include "Component.h"

class C_BaseStat : public Component
{
public:
	C_BaseStat();
	virtual ~C_BaseStat() = 0;

	int GetValue() const;
	void SetValue(int value);

private:
	int m_value;
};

