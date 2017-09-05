#include "PCH.h"
#include "C_Projectile.h"
#include "Object.h"

C_Projectile::C_Projectile() : Component(true), m_velocity({0.f, 0.f})
{
}


C_Projectile::~C_Projectile()
{
}

void C_Projectile::Initialise(const sf::Vector2f& origin, const sf::Vector2f& target)
{
	m_velocity = target - origin;

	float length = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
	m_velocity.x /= length;
	m_velocity.y /= length;
}

void C_Projectile::LoadDependencies(Object* owner)
{
	m_sprite = owner->GetComponent<C_StaticSprite>();
	m_transform = owner->m_transform;
}

void C_Projectile::Update(float timeDelta, Object* owner)
{
	//TODO: move rotation to transform
	m_sprite->GetSprite().setRotation(m_sprite->GetSprite().getRotation() + (400.f * timeDelta));

	m_transform->SetPosition({ m_transform->GetPosition().x + 
		(m_velocity.x * (500 * timeDelta)), m_transform->GetPosition().y + (m_velocity.y * (500 * timeDelta)) });
}
