#include "PCH.h"
#include "C_PlayerTorch.h"
#include "Object.h"
#include "SharedContext.h"

C_PlayerTorch::C_PlayerTorch(Object* owner) : Component(owner, true)
{
}


C_PlayerTorch::~C_PlayerTorch()
{
}

void C_PlayerTorch::Update(float timeDelta, Object* owner)
{
	auto lightGrid = owner->GetContext()->m_lightGrid;

	for (sf::Sprite& sprite : *lightGrid)
	{
		float tileAlpha = 255.f;
		float distance = 0.f;				// The distance between player and tile.

											// Calculate distance between tile and player.
		distance = DistanceBetweenPoints(sprite.getPosition(), owner->m_transform->GetPosition());

		// Calculate tile transparency.
		if (distance < 200.f)
		{
			tileAlpha = 0.f;
		}
		else if (distance < 250.f)
		{
			tileAlpha = (51.f * (distance - 200.f)) / 10.f;
		}

		if (tileAlpha != 255.f)
		{
			sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(tileAlpha)));
		}
	}
}