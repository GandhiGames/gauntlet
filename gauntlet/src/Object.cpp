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

//TODO: remove need for timeDelta
void Object::Update(float timeDelta)
{
	for (std::shared_ptr<Component> component : m_components)
	{
		component->Update(timeDelta);
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
	return;
	//TODO: check actually removes correct/any enemy from list! (because it probably does not!)
	auto it = m_context->m_enemies->begin();
	while (it != m_context->m_enemies->end())
	{
		Object& obj = **it;

		if (obj.m_instanceID->Get() == m_instanceID->Get())
		{
			m_context->m_enemies->erase(it);
			break;
		}
	}
}