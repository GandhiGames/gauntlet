#include "PCH.h"
#include "Entity.h"

// Default constructor.
Entity::Entity() : Object(),
m_currentTextureIndex(static_cast<int>(ANIMATION_STATE::WALK_DOWN))
{
	AddComponent<C_Health>();
	AddComponent<C_Attack>();
	AddComponent<C_Defense>();
	AddComponent<C_Strength>();
	AddComponent<C_Dexterity>();
	AddComponent<C_Stamina>();
	AddComponent<C_Mana>();
}

// Override the default Object::Update function.
void Entity::Update(float timeDelta)
{
	Object::Update(timeDelta);

	// Choose animation state.
	ANIMATION_STATE animState = static_cast<ANIMATION_STATE>(m_currentTextureIndex);

	const sf::Vector2f& velocity = GetComponent<C_Movement>()->GetVelocity();

	if ((velocity.x != 0) || (velocity.y != 0))
	{
		if (abs(velocity.x) > abs(velocity.y))
		{
			if (velocity.x <= 0)
			{
				animState = ANIMATION_STATE::WALK_LEFT;
			}
			else
			{
				animState = ANIMATION_STATE::WALK_RIGHT;
			}
		}
		else
		{
			if (velocity.y <= 0)
			{
				animState = ANIMATION_STATE::WALK_UP;
			}
			else
			{
				animState = ANIMATION_STATE::WALK_DOWN;
			}
		}
	}

	auto sprite = GetComponent<C_AnimatedSprite>();

	// Set animation speed.
	if ((velocity.x == 0) && (velocity.y == 0))
	{
		// The character is still.
		if (sprite->IsAnimated())
		{
			// Update sprite to idle version.
			m_currentTextureIndex += 4;

			// Stop movement animations.
			sprite->SetAnimated(false);
		}
	}
	else
	{
		// The character is moving.
		if (!sprite->IsAnimated())
		{
			// Update sprite to walking version.
			m_currentTextureIndex -= 4;

			// Start movement animations.
			sprite->SetAnimated(true);
		}
	}

	// Set the sprite.
	if (m_currentTextureIndex != static_cast<int>(animState))
	{
		m_currentTextureIndex = static_cast<int>(animState);
		sprite->GetSprite().setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
	}
}

