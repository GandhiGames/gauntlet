//TODO: normalise pragma vs IFNDEF, any reason to still use IFNDEF?
#pragma once

#include "Object.h"

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
	static std::unique_ptr<Object> CreateInstance(ITEM type);
};

