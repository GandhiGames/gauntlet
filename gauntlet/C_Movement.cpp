#include "PCH.h"
#include "C_Movement.h"
#include "Object.h"

C_Movement::C_Movement(Object* owner) : Component(owner, true),
m_velocity({ 0.f, 0.f })
{
}


C_Movement::~C_Movement()
{
}

void C_Movement::LoadDependencies(Object* owner)
{
	m_transform = owner->m_transform;
}

void C_Movement::Update(float timeDelta, Object* owner)
{
	if (abs(m_velocity.x) > 0.f || abs(m_velocity.y) > 0.f)
	{
		m_transform->SetPosition(
			m_transform->GetPosition().x + m_velocity.x,
			m_transform->GetPosition().y + m_velocity.y);
	}
}

void C_Movement::SetVelocity(const sf::Vector2f& velocity)
{
	m_velocity = velocity;
}

const sf::Vector2f& C_Movement::GetVelocity() const
{
	return m_velocity;
}
