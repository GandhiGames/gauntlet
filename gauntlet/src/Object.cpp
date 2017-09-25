#include "PCH.h"
#include "Object.h"
#include "SharedContext.h"

// Transform component automatically added to all new objects.
Object::Object() : m_queuedForRemoval(false)
{
	m_transform = AddComponent<C_Transform>();
	m_instanceID = AddComponent<C_InstanceID>();
	m_tag = AddComponent<C_Tag>();
}

void Object::Update(float timeDelta)
{
	//TODO: cache updateables
	auto updateables = GetComponents<C_Updateable>();
	for (const auto& component : updateables)
	{
		component->Update(timeDelta, this);
	}
}

void Object::LateUpdate(float timeDelta)
{
	//TODO: cache updateables
	auto updateables = GetComponents<C_Updateable>();
	for (const auto& component : updateables)
	{
		component->LateUpdate(timeDelta, this);
	}
}

void Object::Draw(sf::RenderWindow &window, float timeDelta)
{
	//TODO: cache drawables
	auto drawables = GetComponents<C_Drawable>();
	for (const auto& component : drawables)
	{
		component->Draw(window, timeDelta);
	}
}

void Object::OnCollisionEnter(Object* other)
{
	auto collidables = GetComponents<C_Collidable>();
	for (const auto& component : collidables)
	{
		component->OnCollisionEnter(this, other);
	}
}

void Object::OnCollisionExit(Object* other)
{
	auto collidables = GetComponents<C_Collidable>();
	for (const auto& component : collidables)
	{
		component->OnCollisionExit(this, other);
	}
}

void Object::SetContext(SharedContext* context)
{
	m_context = context;
}

SharedContext* Object::GetContext()
{
	return m_context;
}

void Object::Destroy()
{
	//TODO: cache destroyables
	auto updateables = GetComponents<C_OnDeathListener>();
	for (const auto& component : updateables)
	{
		component->OnDeath(this);
	}

	auto children = m_transform->GetChildren();

	if (children.size() > 0)
	{
		for (auto& child : children)
		{
			child->m_owner->Destroy();
		}
	}

	m_queuedForRemoval = true;
}

bool Object::IsQueuedForRemoval() const
{
	return m_queuedForRemoval;
}