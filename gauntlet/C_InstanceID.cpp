#include "PCH.h"
#include "C_InstanceID.h"

int C_InstanceID::count = 0;

C_InstanceID::C_InstanceID() : Component(true)
{
	//TODO: check working as intended.
	m_id = count++;
}


C_InstanceID::~C_InstanceID()
{
}

const int& C_InstanceID::Get()
{
	return m_id;
}
