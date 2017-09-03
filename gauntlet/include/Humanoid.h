//-------------------------------------------------------------------------------------
// Humanoid.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef HUMANOID_H
#define HUMANOID_H

#include "Entity.h"

class Humanoid : public Entity
{
public:

	/**
	 * Default constructor
	 */
	Humanoid();

	/**
	 * Overrides the update event of Enemy.
	 * @param timeDelta The time that has elapsed since the last update.
	 */
	void Update(float timeDelta) override;

	//TODO: make private/move to component
	/**
	* An array of modified textures.
	*/
	sf::Texture m_textures[static_cast<int>(ANIMATION_STATE::COUNT)];


};
#endif