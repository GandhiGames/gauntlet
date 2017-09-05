#pragma once

#include "Entity.h"

class SharedContext
{
public:
	SharedContext();
	~SharedContext();

	std::vector<std::unique_ptr<Entity>>* m_enemies;

	Level* m_level;

	std::vector<std::unique_ptr<Object>>* m_items;

	sf::RenderWindow* m_window;

	std::vector<sf::Sprite>* m_lightGrid;
};

