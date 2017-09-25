#include "PCH.h"
#include "C_Projectile.h"
#include "Object.h"
#include "Level.h"

C_Projectile::C_Projectile(Object* owner) : Component(owner, true), m_velocity({0.f, 0.f})
{
}


C_Projectile::~C_Projectile()
{
}

void C_Projectile::Initialise(const sf::Vector2f& origin, const sf::Vector2f& target,
	const int& damageAmount, const std::string& targetTag)
{
	m_velocity = target - origin;

	float length = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
	m_velocity.x /= length;
	m_velocity.y /= length;

	m_damageAmount = damageAmount;
	m_targetTag = targetTag;
}

void C_Projectile::LoadDependencies(Object* owner)
{
	m_sprite = owner->GetComponent<C_StaticSprite>();
	m_transform = owner->m_transform;
}

void C_Projectile::OnCollisionEnter(Object* owner, Object* other)
{
	if (other->m_tag->Get() == m_targetTag)
	{
		owner->Destroy();

		//TODO: re-implement this
		/*
		if (m_collisionSound != nullptr)
		{
		PlaySound(m_collisionSound);
		}
		*/

	}


}

void C_Projectile::Update(float timeDelta, Object* owner)
{
	//TODO: move rotation to transform
	m_sprite->GetSprite().setRotation(m_sprite->GetSprite().getRotation() + (400.f * timeDelta));

	m_transform->SetPosition({ m_transform->GetPosition().x + 
		(m_velocity.x * (500 * timeDelta)), m_transform->GetPosition().y + (m_velocity.y * (500 * timeDelta)) });

	//Remove if hits wall:
	Tile* projectileTile = owner->GetContext()->m_level->GetTile(owner->m_transform->GetPosition());

	//TODO: should the projectile be removed if tile is nullptr?
	if (projectileTile != nullptr)
	{
		TILE projectileTileType = projectileTile->type;

		if ((projectileTileType != TILE::FLOOR) && (projectileTileType != TILE::FLOOR_ALT))
		{
			owner->Destroy();
		}
	}
}


void C_Projectile::SetSoundOnHit(sf::Sound* collisionSound)
{
	m_collisionSound = collisionSound;
}

const std::string& C_Projectile::GetTargetTag() const
{
	return m_targetTag;
}

const int& C_Projectile::GetDamageAmount() const
{
	return m_damageAmount;
}