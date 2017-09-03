#pragma once

#include<memory>
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
	static EntityFactory* GetInstance();

	std::unique_ptr<Entity> Create(ENEMY type, SharedContext* context);

private:
	EntityFactory();
	static EntityFactory* m_instance;

private:
	sf::Sound m_playerHitSound;
};

