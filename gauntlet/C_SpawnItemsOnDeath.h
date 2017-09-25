#pragma once

#include "C_OnDeathListener.h"
#include "EventHandler.h"

enum class ITEM;

class C_SpawnItemsOnDeath : public C_OnDeathListener
{
	friend class SharedContext;

public:
	C_SpawnItemsOnDeath(Object* owner);
	~C_SpawnItemsOnDeath();

	void OnDeath(Object* owner) override;

private:
	/**
	* Spawns a given item within the level.
	* Be default, the object will be spawned at a random location. There are optional parameters to override and spawn at a given location.
	* @param itemType The type of the item to spawn.
	* @param position The position to spawn the item at.
	*/
	void SpawnItem(ITEM itemType, sf::Vector2f position, SharedContext* context);
};

