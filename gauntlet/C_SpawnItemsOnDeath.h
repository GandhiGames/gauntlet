#pragma once

#include "C_Transform.h"
#include "ItemFactory.h"

class C_SpawnItemsOnDeath : public Component
{
	friend class SharedContext;

public:
	C_SpawnItemsOnDeath();
	~C_SpawnItemsOnDeath();

	void LoadDependencies(Object* owner) override;

private:
	void OnDeath();

	/**
	* Spawns a given item within the level.
	* Be default, the object will be spawned at a random location. There are optional parameters to override and spawn at a given location.
	* @param itemType The type of the item to spawn.
	* @param position The position to spawn the item at.
	*/
	void SpawnItem(ITEM itemType, sf::Vector2f position = { -1.f, -1.f });

private:
	std::shared_ptr<C_Transform> m_transform;

	Object* m_owner;
};
