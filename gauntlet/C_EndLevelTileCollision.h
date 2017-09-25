#pragma once

#include "Component.h"
#include "C_Updateable.h"

class C_EndLevelTileCollision : public Component, public C_Updateable
{
public:
	C_EndLevelTileCollision(Object* owner);
	~C_EndLevelTileCollision();

	void Update(float timeDelta, Object* owner) override;
};

