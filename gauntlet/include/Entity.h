#ifndef ENTITY_H
#define ENTITY_H

#include "Object.h"

//TODO: Remove this class - move update to component system.
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
};
#endif