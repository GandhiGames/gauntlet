#include "PCH.h"
#include "C_Gem.h"
#include "Object.h"

C_Gem::C_Gem(Object* owner) : Component(owner, true)
{
}


C_Gem::~C_Gem()
{
}

void C_Gem::LoadDependencies(Object* owner)
{
	m_points = owner->GetComponent<C_PointsOnPickup>();
}

void C_Gem::OnCollisionEnter(Object* owner, Object* other)
{
	if (other->m_tag->Get() == PLAYER_TAG)
	{
		other->GetComponent<C_Inventory>()->m_score += m_points->GetValue();


		//TODO: re-implement
		// Play the gem pickup sound
		//PlaySound(m_gemPickupSound);

		owner->Destroy();
	}
}
