#pragma once

#include<memory>
#include "Object.h"

// Enemy types.
enum class ENEMY {
	SLIME,
	HUMANOID,
	COUNT
};

class EntityFactory
{
public:
	static EntityFactory* GetInstance();

	std::unique_ptr<Object> Create(ENEMY type, SharedContext* context);

private:
	EntityFactory();
	static EntityFactory* m_instance;

private:
	sf::Sound m_playerHitSound;
};

