 #include "PCH.h"
#include "C_ProjectileAttack.h"
#include "SharedContext.h"
#include "Player.h"
#include "Object.h"

C_ProjectileAttack::C_ProjectileAttack() : Component(true),
	m_projectileTextureID(0),
	m_attackDelta(0.f),
	m_isAttacking(false)
{
}

C_ProjectileAttack::~C_ProjectileAttack()
{
}

void C_ProjectileAttack::LoadDependencies(Object* owner)
{
	m_transform = owner->m_transform;
	m_mana = owner->GetComponent<C_Mana>();

	Player* player = (Player*)owner;

	//TODO: turn class into component
	switch (player->GetClass())
	{
	case PLAYER_CLASS::ARCHER:
		m_projectileTextureID = TextureManager::AddTexture("../resources/projectiles/spr_arrow.png");
		break;
	case PLAYER_CLASS::MAGE:
		m_projectileTextureID = TextureManager::AddTexture("../resources/projectiles/spr_magic_ball.png");
		break;
	case PLAYER_CLASS::THIEF:
		m_projectileTextureID = TextureManager::AddTexture("../resources/projectiles/spr_dagger.png");
		break;
	case PLAYER_CLASS::WARRIOR:
		m_projectileTextureID = TextureManager::AddTexture("../resources/projectiles/spr_sword.png");
		break;
	}

}

void C_ProjectileAttack::Update(float deltaTime, Object* owner)
{
	SharedContext* context = owner->GetContext();
	assert(context);

	auto projectileIterator = m_playerProjectiles.begin();
	while (projectileIterator != m_playerProjectiles.end())
	{
		// Get the projectile object from the iterator.
		Object& projectile = **projectileIterator;

		// Get the tile that the projectile is on.
		Tile* projectileTile = context->m_level->GetTile(projectile.m_transform->GetPosition());
		
		if (projectileTile != nullptr)
		{
 			TILE projectileTileType = projectileTile->type;

			// If the tile the projectile is on is not floor, delete it.
			if ((projectileTileType != TILE::FLOOR) && (projectileTileType != TILE::FLOOR_ALT))
			{
				projectileIterator = m_playerProjectiles.erase(projectileIterator);
			}
			else
			{
				// Update the projectile and move to the next one.
				projectile.Update(deltaTime);
				++projectileIterator;
			}
		}
		else
		{
			//TODO: remove perception.
			projectile.Update(deltaTime);
			++projectileIterator;
		}
	}

	if ((m_attackDelta += deltaTime) > 0.25f)
	{
		if (Input::IsKeyPressed(Input::KEY::KEY_ATTACK))
		{
			int curMana = m_mana->GetCurrent();
			if (curMana >= 2)
			{
				//TODO: cache screenCentre.
				sf::Vector2f m_screenCenter = { context->m_window->getSize().x / 2.f, context->m_window->getSize().y / 2.f };

				//TODO: move to object pool.
				sf::Vector2f target(static_cast<float>(sf::Mouse::getPosition().x), static_cast<float>(sf::Mouse::getPosition().y));
				std::unique_ptr<Object> proj = std::make_unique<Object>();
				proj->SetContext(context);

				auto sprite = proj->AddComponent<C_StaticSprite>();
				//TODO: cache texture get.
				sprite->SetSprite(TextureManager::GetTexture(m_projectileTextureID));

				auto projComp = proj->AddComponent<C_Projectile>();
				projComp->Initialise(m_screenCenter, target);

				proj->m_tag->Set(PROJECTILE_TAG);
				proj->m_transform->SetPosition(m_transform->GetPosition());

				auto dmg = proj->AddComponent<C_CollisionDamage>();
				dmg->SetDamageAmount(25);
				dmg->SetTargetTag(ENEMY_TAG);

				m_playerProjectiles.push_back(std::move(proj));
				m_mana->SetCurrent(curMana - 2);

				m_attackDelta = 0.f;
			}
		}
	}
}

void C_ProjectileAttack::Draw(sf::RenderWindow &window, float timeDelta)
{
	for (const auto& proj : m_playerProjectiles)
	{
		auto sprite = proj->GetComponent<C_StaticSprite>();

		if (sprite)
		{
			sprite->Draw(window, timeDelta);
		}
	}
}
