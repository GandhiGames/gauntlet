#include "PCH.h"
#include "C_StaticSprite.h"
#include "Object.h"

//TODO: shouldn't need to set unique on both drawable and updateable
C_StaticSprite::C_StaticSprite(Object* owner) : Component(owner, true)
{
	
}

C_StaticSprite::~C_StaticSprite()
{
}

void C_StaticSprite::LoadDependencies(Object* owner)
{
	assert(owner->GetComponents<C_Drawable>().size() == 0);

	m_transform = owner->m_transform;
}

void C_StaticSprite::Update(float deltaTime, Object* owner)
{
	m_sprite.setPosition(m_transform->GetPosition());
}

// Draws the object to the given render window.
void C_StaticSprite::Draw(sf::RenderWindow &window, float timeDelta)
{
	window.draw(m_sprite);
}

// Gives the object the given sprite.
bool C_StaticSprite::SetSprite(sf::Texture& texture)
{
	// Create a sprite from the loaded texture.
	m_sprite.setTexture(texture);

	
	// Calculate frame dimensions.
	sf::Vector2u texSize = m_sprite.getTexture()->getSize();
	unsigned int width = texSize.x;
	unsigned int height = texSize.y;

	// Set the origin of the sprite.
	m_sprite.setOrigin(width / 2.f, height / 2.f);

	return true;
}

//TODO: remove this function and provide functionality through different methods.
sf::Sprite& C_StaticSprite::GetSprite()
{
	return m_sprite;
}



