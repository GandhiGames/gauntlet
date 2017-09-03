#include "PCH.h"
#include "C_SpawnItemsOnDeath.h"
#include "Object.h"
#include "SharedContext.h"
#include "Level.h"

C_SpawnItemsOnDeath::C_SpawnItemsOnDeath() : Component(true)
{
}


C_SpawnItemsOnDeath::~C_SpawnItemsOnDeath()
{
}

void C_SpawnItemsOnDeath::LoadDependencies(Object* owner)
{
	//owner->GetComponent<C_Health>()->PerformActionOnDeath(OnDeath);
	m_transform = owner->m_transform;

	//TODO: any component that wants context should store reference to owner instance of context as sometimes context will be set after 
	// load dependencies is called causing an ordering issue.
	m_owner = owner;
}

void C_SpawnItemsOnDeath::OnDeath()
{
	// Get the enemy position.
	sf::Vector2f position = m_transform->GetPosition();

	// Spawn loot.
	for (int i = 0; i < 5; i++)
	{
		position.x += std::rand() % 31 - 15;
		position.y += std::rand() % 31 - 15;
		SpawnItem(static_cast<ITEM>(std::rand() % 2), position);	// Generates a number 0 - 1
	}

	if ((std::rand() % 5) == 0)			// 1 in 5 change of spawning health.
	{
		position.x += std::rand() % 31 - 15;
		position.y += std::rand() % 31 - 15;
		SpawnItem(ITEM::HEART, position);
	}
	// 1 in 5 change of spawning potion.
	else if ((std::rand() % 5) == 1)
	{
		position.x += std::rand() % 31 - 15;
		position.y += std::rand() % 31 - 15;
		SpawnItem(ITEM::POTION, position);
	}
}

// Spawns a given object type at a random location within the map. Has the option to explicitly set a spawn location.
void C_SpawnItemsOnDeath::SpawnItem(ITEM itemType, sf::Vector2f position)
{
	int objectIndex = 0;

	// Choose a random, unused spawn location.
	sf::Vector2f spawnLocation;

	SharedContext* context = m_owner->GetContext();

	if ((position.x >= 0.f) || (position.y >= 0.f))
	{
		spawnLocation = position;
	}
	else
	{
		spawnLocation = context->m_level->GetRandomSpawnLocation();
	}

	std::unique_ptr<Item> item = ItemFactory::CreateInstance(itemType);
	item->SetContext(context);

	// Set the item position.
	item->m_transform->SetPosition(spawnLocation);
	context->m_items->push_back(std::move(item));
}
