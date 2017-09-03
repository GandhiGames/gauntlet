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
	m_transform = owner->GetComponent<C_Transform>();
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

	m_context = owner->GetContext();

	m_screenCenter = { m_context->m_window->getSize().x / 2.f, m_context->m_window->getSize().y / 2.f };
}

void C_ProjectileAttack::Update(float deltaTime)
{
	auto projectileIterator = m_playerProjectiles.begin();
	while (projectileIterator != m_playerProjectiles.end())
	{
		// Get the projectile object from the iterator.
		Projectile& projectile = **projectileIterator;

		// Get the tile that the projectile is on.
		TILE projectileTileType = m_context->m_level->GetTile(projectile.m_transform->GetPosition())->type;

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

	if ((m_attackDelta += deltaTime) > 0.25f)
	{
		if (Input::IsKeyPressed(Input::KEY::KEY_ATTACK))
		{
			int curMana = m_mana->GetCurrent();
			if (curMana >= 2)
			{
				sf::Vector2f target(static_cast<float>(sf::Mouse::getPosition().x), static_cast<float>(sf::Mouse::getPosition().y));
				std::unique_ptr<Projectile> proj = std::make_unique<Projectile>(TextureManager::GetTexture(m_projectileTextureID), 
					m_transform->GetPosition(), m_screenCenter, target);
				proj->SetContext(m_context);
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
