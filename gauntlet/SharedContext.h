#pragma once

#include "Object.h"

class SharedContext
{
	friend class Game;
public:
	SharedContext();
	~SharedContext();

	std::vector<std::unique_ptr<Object>>* m_newObjects;
	std::vector<std::unique_ptr<Object>>* m_objects;
	
	Level* m_level;

	sf::RenderWindow* m_window;

	std::vector<sf::Sprite>* m_lightGrid;

	Object* m_player;

	Game* m_game;
};

