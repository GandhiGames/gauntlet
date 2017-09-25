#include "PCH.h"
#include "C_Gold.h"
#include "Object.h"

C_Gold::C_Gold(Object* owner) : Component(owner, true)
{
}


C_Gold::~C_Gold()
{
}

void C_Gold::LoadDependencies(Object* owner)
{
	m_points = owner->GetComponent<C_PointsOnPickup>();
}

void C_Gold::OnCollisionEnter(Object* owner, Object* other)
{
	if (other->m_tag->Get() == PLAYER_TAG)
	{
		other->GetComponent<C_Inventory>()->m_gold += m_points->GetValue();

		//TODO: re-implement this.
		// Play gold collect sound effect.
		//PlaySound(m_coinPickupSound);

		owner->Destroy();
	}
}
