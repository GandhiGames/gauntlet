#pragma once

#include<memory>
#include "Enemy.h"
#include "Humanoid.h"

// Enemy types.
enum class ENEMY {
	SLIME,
	HUMANOID,
	COUNT
};

class EntityFactory
{
public:
	//TODO: should this return reference?
	static std::unique_ptr<Enemy> CreateInstance(ENEMY type);
};

