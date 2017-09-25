#include "PCH.h"
#include "C_Key.h"
#include "Object.h"
#include "SharedContext.h"
#include "Level.h"

C_Key::C_Key(Object* owner) : Component(owner, true)
{
}


C_Key::~C_Key()
{
}

void C_Key::OnCollisionEnter(Object* owner, Object* other)
{
	owner->GetContext()->m_level->UnlockDoor();

	//TODO: re-implement this
	// Play key collect sound.
	//PlaySound(m_keyPickupSound);

	//TODO: re-implement this
	// Set the key as collected.
	//m_keyUiSprite->setColor(sf::Color::White);

	owner->Destroy();
}
