#ifndef ITEM_H
#define ITEM_H

#include <sstream>
#include <fstream>
#include "Object.h"

//TODO: should this be a friend class?
enum class ITEM;

class Item : public Object
{
public:
	/**
	 * Default constructor.
	 */
	Item();

	void SetType(ITEM type);

	/**
	 * Gets the item type.
	 * @return The item type.
	 */
	ITEM GetType() const;

public:
	/**
	 * The type of item.
	 */
	ITEM m_type;
};
#endif