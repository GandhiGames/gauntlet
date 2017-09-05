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
	//TODO: re-implement below:
	//owner->GetComponent<C_Health>()->PerformActionOnDeath(OnDeath);

	m_transform = owner->m_transform;
}

void C_SpawnItemsOnDeath::Update(float deltaTime, Object* owner)
{
	//TODO: get rid of this! remove update method completely!
	if (owner && !m_owner)
	{
		m_owner = owner;
	}
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

void C_SpawnItemsOnDeath::SpawnItem(ITEM itemType, 
	sf::Vector2f position)
{

	SharedContext* context = m_owner->GetContext();

	int objectIndex = 0;

	std::unique_ptr<Object> item = ItemFactory::CreateInstance(itemType);
	item->SetContext(context);

	// Set the item position.
	item->m_transform->SetPosition(position);
	context->m_items->push_back(std::move(item));
}
