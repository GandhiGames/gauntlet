//-------------------------------------------------------------------------------------
// Item.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef ITEM_H
#define ITEM_H

#include <sstream>
#include <fstream>
#include "Object.h"

//TODO: should this be a friend class?u
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