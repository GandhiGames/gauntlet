#include "PCH.h"
#include "Projectile.h"

// Default constructor.
Projectile::Projectile(sf::Texture& texture, sf::Vector2f origin, sf::Vector2f screenCenter, sf::Vector2f target)
{
	auto sprite = AddComponent<C_Sprite>();
	sprite->SetSprite(texture, false);

	// Set the position.
	m_transform->SetPosition(origin);

	//TODO: move velocity into seperate component
	m_velocity = target - screenCenter;

	float length = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
	m_velocity.x /= length;
	m_velocity.y /= length;
}

// Update the projectile.
void Projectile::Update(float timeDelta)
{
	__super::Update(timeDelta);

	auto sprite = GetComponent<C_Sprite>();

	//TODO: move rotation to transform
	sprite->GetSprite().setRotation(sprite->GetSprite().getRotation() + (400.f * timeDelta));

	m_transform->SetPosition({ m_transform->GetPosition().x + (m_velocity.x * (500 * timeDelta)), m_transform->GetPosition().y + (m_velocity.y * (500 * timeDelta)) });
}