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

#include "Entity.h"
#include "Input.h"
#include "Level.h"
#include "Projectile.h"

class Player : public Entity
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

	/**
	 * Chooses random traits for the character.
	 */
	void SetRandomTraits();

	/**
	 * Gets the player's class.
	 * @return The player's class.
	 */
	PLAYER_CLASS GetClass() const;

private:

	/**
	 * Checks if the given movement will result in a collision.
	 * @param movement The movement to check.
	 * @param level A reference to the level object.
	 * @return True if the given movement will result in a collision.
	 */
	bool CausesCollision(sf::Vector2f movement, Level& level);

private:

	int m_speed;

	/**
	 * The number of traits that the player can have.
	 */
	static const int PLAYER_TRAIT_COUNT = 2;

	/**
	 * An array containing the character's traits.
	 */
	PLAYER_TRAIT m_traits[PLAYER_TRAIT_COUNT];

	/**
	 * The player's class.
	 */
	PLAYER_CLASS m_class;

	

	/**
	 * The time since the last mana regeneration.
	 */
	float m_manaDelta;


	/**
	* The number of stat points the entities has to distribute.
	*/
	int m_statPoints;
};
#endif