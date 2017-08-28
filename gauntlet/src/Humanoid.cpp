#include "PCH.h"
#include "Humanoid.h"

// Default constructor.
Humanoid::Humanoid()
{
}

// Overrides the update event of Enemy.
void Humanoid::Update(float timeDelta)
{
	// Call parent functionality.
	Enemy::Update(timeDelta);

	// Update the texture with our custom textures.
	GetComponent<C_Sprite>()->GetSprite().setTexture(m_textures[m_currentTextureIndex]);
}