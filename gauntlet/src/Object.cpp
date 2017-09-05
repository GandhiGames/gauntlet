#include "PCH.h"
#include "Object.h"
#include "SharedContext.h"

// Transform component automatically added to all new objects.
Object::Object()
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

void Object::Draw(sf::RenderWindow &window, float timeDelta)
{
	//TODO: cache drawables
	auto drawables = GetComponents<C_Drawable>();
	for (const auto& component : drawables)
	{
		component->Draw(window, timeDelta);
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
	//TODO: check actually removes correct/any enemy from list! (because it probably does not!)
	//TODO: only removes object if contained in enemy list, should remove regardless of list (create global list)
	/*
	for (const auto& obj : *m_context->m_enemies)
	{
		if (obj->m_instanceID->Get() == m_instanceID->Get())
		{
			m_context->m_enemies->erase(obj);
			break;
		}
	}
	*/
	
	auto it = m_context->m_enemies->begin();
	while (it != m_context->m_enemies->end())
	{
		Object& obj = **it;

		if (obj.m_instanceID->Get() == m_instanceID->Get())
		{
			m_context->m_enemies->erase(it);
			break;
		}

		++it;
	}
}