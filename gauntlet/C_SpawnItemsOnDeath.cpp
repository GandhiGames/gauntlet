#include "PCH.h"
#include "C_SpawnItemsOnDeath.h"
#include "Object.h"
#include "SharedContext.h"
#include "Level.h"

C_SpawnItemsOnDeath::C_SpawnItemsOnDeath(Object* owner) : C_OnDeathListener(owner, true)
{
}


C_SpawnItemsOnDeath::~C_SpawnItemsOnDeath()
{
}


void C_SpawnItemsOnDeath::OnDeath(Object* owner) 
{
	// Get the enemy position.
	sf::Vector2f position = owner->m_transform->GetPosition();

	SharedContext* context = owner->GetContext();

	// Spawn loot.
	for (int i = 0; i < 5; i++)
	{
		position.x += std::rand() % 31 - 15;
		position.y += std::rand() % 31 - 15;
		SpawnItem(static_cast<ITEM>(std::rand() % 2), position, context);	// Generates a number 0 - 1
	}

	if ((std::rand() % 5) == 0)			// 1 in 5 change of spawning health.
	{
		position.x += std::rand() % 31 - 15;
		position.y += std::rand() % 31 - 15;
		SpawnItem(ITEM::HEART, position, context);
	}
	// 1 in 5 change of spawning potion.
	else if ((std::rand() % 5) == 1)
	{
		position.x += std::rand() % 31 - 15;
		position.y += std::rand() % 31 - 15;
		SpawnItem(ITEM::POTION, position, context);
	}
}

void C_SpawnItemsOnDeath::SpawnItem(ITEM itemType,
	sf::Vector2f position, SharedContext* context)
{
	int objectIndex = 0;

	std::unique_ptr<Object> item = ItemFactory::CreateInstance(itemType);
	item->SetContext(context);

	// Set the item position.
	item->m_transform->SetPosition(position);
	context->m_newObjects->push_back(std::move(item));
}
