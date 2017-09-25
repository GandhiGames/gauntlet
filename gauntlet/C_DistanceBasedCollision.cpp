#include "PCH.h"
#include "C_DistanceBasedCollision.h"
#include "Object.h"
#include "SharedContext.h"

C_DistanceBasedCollision::C_DistanceBasedCollision(Object* owner) : Component(owner, true)
{
}


C_DistanceBasedCollision::~C_DistanceBasedCollision()
{
}

void C_DistanceBasedCollision::Update(float deltaTime, Object* owner)
{
	const int& thisId = owner->m_instanceID->Get();

	SharedContext* context = owner->GetContext();

	
	for (const auto& other : *context->m_objects)
	{
		auto collidables = other->GetComponent<C_Collidable>();

		if (collidables == nullptr)
		{
			continue;
		}

		const int id = other->m_instanceID->Get();

		if (id == thisId)
		{
			continue;
		}

		if (DistanceBetweenPoints(other->m_transform->GetPosition(), owner->m_transform->GetPosition()) < 40.f)
		{
			if (m_colliding.find(id) == m_colliding.end())
			{
				other->OnCollisionEnter(owner);
				m_colliding.emplace(id);
			}
		}
		else
		{
			if (m_colliding.find(id) != m_colliding.end())
			{
				other->OnCollisionExit(owner);
				//TODO: what happens when enemy removed from game - it needs
				// to be removed from this list to!
				m_colliding.erase(id);
			}
		}
	}


	Object* player = owner->GetContext()->m_player;

	const int id = player->m_instanceID->Get();

	if (id != thisId)
	{
		if (DistanceBetweenPoints(player->m_transform->GetPosition(), owner->m_transform->GetPosition()) < 40.f)
		{
			if (m_colliding.find(id) == m_colliding.end())
			{
				player->OnCollisionEnter(owner);
				m_colliding.emplace(id);
			}
		}
		else
		{
			if (m_colliding.find(id) != m_colliding.end())
			{
				player->OnCollisionExit(owner);
				m_colliding.erase(id);
			}
		}
	}
}
