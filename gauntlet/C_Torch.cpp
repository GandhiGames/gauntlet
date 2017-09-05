#include "PCH.h"
#include "C_Torch.h"
#include "Object.h"
#include "SharedContext.h"

C_Torch::C_Torch() : Component(true), m_brightness(1.f)
{
}


C_Torch::~C_Torch()
{
}


void C_Torch::Update(float timeDelta, Object* owner)
{
	m_brightness = (std::rand() % 41 + 80) / 100.f;

	SharedContext* context = owner->GetContext();

	for (auto& sprite : *context->m_lightGrid)
	{
		float distance = DistanceBetweenPoints(sprite.getPosition(), owner->m_transform->GetPosition());

		if (distance < 100.f)
		{
			float tileAlpha = 255.f;

			tileAlpha -= (tileAlpha - ((tileAlpha / 100.f) * distance)) * m_brightness;

			// Ensure alpha does not go negative.
			if (tileAlpha < 0)
			{
				tileAlpha = 0;
			}

			// Set the sprite transparency.
			sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(tileAlpha)));

		}
	}
}

//TODO: this also exists in game.cpp, move to utils class.
float C_Torch::DistanceBetweenPoints(sf::Vector2f position1, sf::Vector2f position2)
{
	return (abs(sqrt(((position1.x - position2.x) * (position1.x - position2.x)) + ((position1.y - position2.y) * (position1.y - position2.y)))));
}
