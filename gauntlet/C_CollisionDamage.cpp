#include "PCH.h"
#include "SharedContext.h"
#include "C_CollisionDamage.h"
#include "Level.h"

//TODO: optomise if multiple collision damages added to same object, don't need to each have seperate loops each update.
C_CollisionDamage::C_CollisionDamage() : Component(false)
{
}


C_CollisionDamage::~C_CollisionDamage()
{
}


void C_CollisionDamage::LoadDependencies(Object* owner)
{
	m_transform = owner->m_transform;
}

//TODO: rename class to tile collision damage.
//TODO: create bounding box version.
void C_CollisionDamage::Update(float deltaTime, Object* owner)
{
	SharedContext* context = owner->GetContext();
	assert(owner);

	Tile* curTile = context->m_level->GetTile(m_transform->GetPosition());

	//TODO: need to have a standard objects list (no seperate lists for enemies etc).
	auto enemyIterator = context->m_enemies->begin();
	while (enemyIterator != context->m_enemies->end())
	{
		// Get the enemy object from the iterator.
		Entity& other = **enemyIterator;

		if (m_targetTag == ENEMY_TAG)
		{
			printf("dont care");
		}

		if (other.m_tag->Get() == m_targetTag)
		{
			// Get the tile that the enemy is on.
			Tile* enemyTile = context->m_level->GetTile(other.m_transform->GetPosition());

			if (enemyTile == curTile)
			{
				auto damageables = other.GetComponents<C_Damageable>();

				for (const auto& d : damageables)
				{
					d->DoDamage(m_damageAmount);
				}

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

		++enemyIterator;
	}
}

void C_CollisionDamage::SetDamageAmount(int amount)
{
	m_damageAmount = amount;
}

void C_CollisionDamage::SetTargetTag(std::string tag)
{
	m_targetTag = tag;
}

void C_CollisionDamage::SetSoundOnHit(sf::Sound* collisionSound)
{
	m_collisionSound = collisionSound;
}

//TODO: this function is all over the place. Centralise and remove duplicates!
void C_CollisionDamage::PlaySound(sf::Sound* sound, sf::Vector2f position)
{
	// Generate and set a random pitch.
	float pitch = (std::rand() % 11 + 95) / 100.f;
	sound->setPitch(pitch);

	// Set the position of the sound.
	sound->setPosition(position.x, position.y, 0.f);

	// Play the sound.
	sound->play();
}
