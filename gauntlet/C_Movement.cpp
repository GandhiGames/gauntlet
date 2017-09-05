#include "PCH.h"
#include "C_Movement.h"
#include "Object.h"

C_Movement::C_Movement() : Component(true),
m_speed(0),
m_velocity({ 0.f, 0.f })
{
	m_speed = rand() % 51 + 150;
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
	float length = sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
	m_velocity.x /= length;
	m_velocity.y /= length;

	m_transform->SetPosition(
		m_transform->GetPosition().x + m_velocity.x * (m_speed * timeDelta),
		m_transform->GetPosition().y + m_velocity.y * (m_speed * timeDelta));
}

void C_Movement::SetVelocity(const sf::Vector2f& velocity)
{
	m_velocity = velocity;
}

const sf::Vector2f& C_Movement::GetVelocity() const
{
	return m_velocity;
}
