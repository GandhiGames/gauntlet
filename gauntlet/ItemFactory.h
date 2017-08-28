#pragma once

#include "Item.h"

// Spawnable items.
enum class ITEM {
	GEM,
	GOLD,
	HEART,
	POTION,
	KEY,
	COUNT
};


class ItemFactory
{
public:
	static std::unique_ptr<Item> CreateInstance(ITEM type);
};

