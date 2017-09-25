 #include "PCH.h"
#include "C_ProjectileAttack.h"
#include "SharedContext.h"
#include "Player.h"
#include "Object.h"

C_ProjectileAttack::C_ProjectileAttack(Object* owner) : Component(owner, true),
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
	switch (player->GetComponent<C_PlayerClass>()->Get())
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
				projComp->Initialise(m_screenCenter, target, 25, ENEMY_TAG);

				proj->m_tag->Set(PROJECTILE_TAG);
				proj->m_transform->SetPosition(m_transform->GetPosition());

				
				proj->AddComponent<C_DistanceBasedCollision>();

				context->m_objects->push_back(std::move(proj));
				m_mana->SetCurrent(curMana - 2);

				m_attackDelta = 0.f;
			}
		}
	}
}

