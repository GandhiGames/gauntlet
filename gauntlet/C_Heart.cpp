#include "PCH.h"
#include "C_Heart.h"
#include "Object.h"

C_Heart::C_Heart(Object* owner) : Component(owner, true)
{
}


C_Heart::~C_Heart()
{
}

void C_Heart::LoadDependencies(Object* owner)
{
	m_healthToAdd = owner->GetComponent<C_PointsOnPickup>();
}

void C_Heart::OnCollisionEnter(Object* owner, Object* other)
{
	if (owner->m_tag->Get() == PLAYER_TAG)
	{
		auto health = other->GetComponent<C_Health>();
		health->SetCurrent(health->GetCurrent() + m_healthToAdd->GetValue());

		owner->Destroy();
	}
}
