#include "PCH.h"
#include "C_AudioListener.h"
#include "Object.h"

C_AudioListener::C_AudioListener(Object* owner) : Component(owner, true)
{
}


C_AudioListener::~C_AudioListener()
{
}

void C_AudioListener::LoadDependencies(Object* owner) 
{
	m_transform = owner->m_transform;
}

void C_AudioListener::Update(float deltaTime, Object* owner) 
{
	const sf::Vector2f& pos = m_transform->GetPosition();
	sf::Listener::setPosition(pos.x, pos.y, 0.f);
}
