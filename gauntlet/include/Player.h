//-------------------------------------------------------------------------------------
// Player.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"
#include "Input.h"
#include "Level.h"

class Player : public Object
{
public:
	/**
	 * Default constructor.
	 */
	Player();

	/**
	 * Updates the player object.
	 * The main purpose of this function is to update the players position.
	 * @param timeDelta The time, in MS, since the last game tick.
	 * @param level A reference to the level object.
	 */
	void Update(float timeDelta, Level& level);

	/**
	 * Gets the player's current traits.
	 * @return The player's current traits.
	 */
	PLAYER_TRAIT* GetTraits();

	/**
	 * Gets the number of traits the player has.
	 */
	int GetTraitCount() const;



private:
	/**
	* Chooses random traits for the character.
	*/
	void SetRandomTraits();

	/**
	 * The number of traits that the player can have.
	 */
	static const int PLAYER_TRAIT_COUNT = 2;

	/**
	 * An array containing the character's traits.
	 */
	PLAYER_TRAIT m_traits[PLAYER_TRAIT_COUNT];
};
#endif