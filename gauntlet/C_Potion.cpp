#include "PCH.h"
#include "C_Potion.h"
#include "Object.h"

C_Potion::C_Potion(Object* owner) : Component(owner, true)
{
}


C_Potion::~C_Potion()
{
}

void C_Potion::LoadDependencies(Object* owner)
{
	m_type = owner->GetComponent<C_PotionType>();
	m_points = owner->GetComponent<C_PointsOnPickup>();
}

void C_Potion::OnCollisionEnter(Object* owner, Object* other)
{
	if (other->m_tag->Get() == PLAYER_TAG)
	{
		switch (m_type->Get())
		{
		case POTION::ATTACK:
		{
			auto attack = other->GetComponent<C_Attack>();
			attack->SetValue(attack->GetValue() + m_points->GetValue());
			break;
		}
		case POTION::DEFENSE:
		{
			auto defense = other->GetComponent<C_Defense>();
			defense->SetValue(defense->GetValue() + m_points->GetValue());
			break;
		}
		case POTION::STRENGTH:
		{
			auto strength = other->GetComponent<C_Strength>();
			strength->SetValue(strength->GetValue() + m_points->GetValue());
			break;
		}
		case POTION::DEXTERITY:
		{
			auto dexterity = other->GetComponent<C_Dexterity>();
			dexterity->SetValue(dexterity->GetValue() + m_points->GetValue());
			break;
		}
		case POTION::STAMINA:
		{
			auto stamina = other->GetComponent<C_Stamina>();
			stamina->SetValue(stamina->GetValue() + m_points->GetValue());

			break;
		}
		}

		owner->Destroy();
	}
}
