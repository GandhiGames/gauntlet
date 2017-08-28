#include "PCH.h"
#include "Object.h"

// Transform component automatically added to all new objects.
Object::Object()
{
	m_transform = AddComponent<C_Transform>();
}

//TODO: remove need for timeDelta
void Object::Update(float timeDelta)
{
	for (std::shared_ptr<Component> component : m_components)
	{
		component->Update(timeDelta);
	}
};
