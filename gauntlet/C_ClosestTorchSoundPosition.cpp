#include "PCH.h"
#include "C_ClosestTorchSoundPosition.h"
#include "Object.h"
#include "SharedContext.h"
#include "Level.h"

//TODO: create object, add this component, and add to global updte list.
C_ClosestTorchSoundPosition::C_ClosestTorchSoundPosition(Object* owner) : Component(owner, true)
{
	int soundBufferId = SoundBufferManager::AddSoundBuffer("../resources/sounds/snd_fire.wav");
	m_fireSound.setBuffer(SoundBufferManager::GetSoundBuffer(soundBufferId));
	m_fireSound.setLoop(true);
	m_fireSound.setAttenuation(5.f);
	m_fireSound.setMinDistance(80.f);
	m_fireSound.play();
}


C_ClosestTorchSoundPosition::~C_ClosestTorchSoundPosition()
{
}

void C_ClosestTorchSoundPosition::Update(float deltaTime, Object* owner)
{
	SharedContext* context = owner->GetContext();

	auto torches = context->m_level->GetTorches();

	const sf::Vector2f& playerPosition = context->m_player->m_transform->GetPosition();

	// If there are torches.
	if (!torches->empty())
	{
		// Store the first torch as the current closest.
		std::shared_ptr<Object> nearestTorch = torches->front();
		float lowestDistanceToPlayer = 
			DistanceBetweenPoints(playerPosition, 
			nearestTorch->m_transform->GetPosition());

		for (std::shared_ptr<Object> torch : *torches)
		{
			// Get the distance to the player.
			float distanceToPlayer = 
				DistanceBetweenPoints(playerPosition, 
				torch->m_transform->GetPosition());

			if (distanceToPlayer < lowestDistanceToPlayer)
			{
				lowestDistanceToPlayer = distanceToPlayer;
				nearestTorch = torch;
			}
		}

		m_fireSound.setPosition(nearestTorch->m_transform->GetPosition().x, nearestTorch->m_transform->GetPosition().y, 0.0f);
	}
}
