#pragma once

#include "Component.h"

class C_PlayerClass : public Component
{
public:
	C_PlayerClass(Object* owner);
	~C_PlayerClass();

	void Set(PLAYER_CLASS playerClass);
	const PLAYER_CLASS& Get() const;

private:
	PLAYER_CLASS m_class;
};

