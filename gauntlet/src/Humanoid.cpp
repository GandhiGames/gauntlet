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
	Object::Update(timeDelta);
	//int m_textureIDs[static_cast<int>(ANIMATION_STATE::COUNT)];
	// Update the texture with our custom textures.
	//auto textureId = GetComponent<C_DirectionalAnimation>()->GetTextureID();
	//GetComponent<C_AnimatedSprite>()->GetSprite().setTexture(m_textures[textureId]);
}