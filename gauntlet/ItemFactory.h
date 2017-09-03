//TODO: normalise pragma vs IFNDEF, any reason to still use IFNDEF?
#pragma once

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
	friend class Item;
public:
	static std::unique_ptr<Item> CreateInstance(ITEM type);
};

