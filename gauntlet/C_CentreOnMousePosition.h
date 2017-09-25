#pragma once

#include "Component.h"
#include "C_Updateable.h"

class C_CentreOnMousePosition : public Component, public C_Updateable
{
public:
	C_CentreOnMousePosition(Object* owner);
	~C_CentreOnMousePosition();

	void Update(float timeDelta, Object* owner) override;
};

