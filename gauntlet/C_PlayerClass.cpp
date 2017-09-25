#include "PCH.h"
#include "C_PlayerClass.h"


C_PlayerClass::C_PlayerClass(Object* owner) : Component(owner, true)
{
}


C_PlayerClass::~C_PlayerClass()
{
}

void C_PlayerClass::Set(PLAYER_CLASS playerClass)
{
	m_class = playerClass;
}

const PLAYER_CLASS& C_PlayerClass::Get() const
{
	return m_class;
}
