#include "PCH.h"
#include "C_CentreOnMousePosition.h"
#include "Object.h"

C_CentreOnMousePosition::C_CentreOnMousePosition(Object* owner) : Component(owner, true)
{
}


C_CentreOnMousePosition::~C_CentreOnMousePosition()
{
}

void C_CentreOnMousePosition::Update(float timeDelta, Object* owner)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	owner->m_transform->SetPosition((float)mousePos.x, (float)mousePos.y);
}
