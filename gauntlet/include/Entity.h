//-------------------------------------------------------------------------------------
// Enemy.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef ENTITY_H
#define ENTITY_H

#include "Object.h"

//TODO: Remove this class?
class Entity : public Object
{
public:

	/**
	 * Default constructor.
	 */
	Entity();

	/**
	 * Override the default Object::Update function.
	 * @param timeDelta The time that has elapsed since the last update.
	 */
	virtual void Update(float timeDelta) override;

	//TODO: make private and move into animatedsprite component.
	int m_textureIDs[static_cast<int>(ANIMATION_STATE::COUNT)];

protected:


	/**
	 * The index of the current texture.
	 */
	int m_currentTextureIndex;

	/**
	 * The entities current velocity.
	 */
	sf::Vector2f m_velocity;
};
#endif