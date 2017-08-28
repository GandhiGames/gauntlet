#include "PCH.h"
#include "Enemy.h"

// Default constructor.
Enemy::Enemy() 
{
	AddComponent<C_Sprite>();

	m_pathFinding = AddComponent<C_Pathfinding>();

	GetComponent<C_Health>()->SetCurrent(std::rand() % 41 + 80);
	GetComponent<C_Attack>()->SetValue(std::rand() % 5 + 6);
	GetComponent<C_Defense>()->SetValue(std::rand() % 5 + 6);
	GetComponent<C_Strength>()->SetValue(std::rand() % 5 + 6);
	GetComponent<C_Dexterity>()->SetValue(std::rand() % 5 + 6);
	GetComponent<C_Stamina>()->SetValue(std::rand() % 5 + 6);

}


