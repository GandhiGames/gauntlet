#include "PCH.h"
#include "C_Transform.h"

C_Transform::C_Transform(Object* owner) : Component(owner, true),
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

const sf::Vector2f& C_Transform::GetPosition() const
{
	if (m_parent == nullptr)
	{
		return m_position;
	}
	else
	{
		const sf::Vector2f& position = m_parent->GetPosition() + m_position;
		return position;
	}
}

void C_Transform::SetParent(std::shared_ptr<C_Transform> parent)
{
	m_parent = parent;

	m_parent->AddChild(this);
}

const std::shared_ptr<C_Transform> C_Transform::GetParent() const
{
	return m_parent;
}

void C_Transform::AddChild(C_Transform* child)
{
	m_children.push_back(child);
}

const std::vector<C_Transform*>& C_Transform::GetChildren() const
{
	return m_children;
}
