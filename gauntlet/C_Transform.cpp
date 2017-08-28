#include "PCH.h"
#include "C_Transform.h"

C_Transform::C_Transform() : Component(true),
	m_position({ 0.f, 0.f }) {}

C_Transform::~C_Transform() {}

// Sets the position of the object.
void C_Transform::SetPosition(sf::Vector2f position)
{
	m_position = position;
}

void C_Transform::SetPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}

void C_Transform::SetX(float x)
{
	m_position.x = x;
}

void C_Transform::SetY(float y)
{
	m_position.y = y;
}


// Returns the position of the object.
const sf::Vector2f& C_Transform::GetPosition() const
{
	return m_position;
}
