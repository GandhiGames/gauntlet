#pragma once

#include "Component.h"

class C_InstanceID : public Component
{
public:
	C_InstanceID();
	~C_InstanceID();

	const int& Get();

private:
	static int count;
	int m_id;
};

