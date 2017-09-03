#include "PCH.h"
#include "C_PlaySoundOnDeath.h"
#include "Object.h"


C_PlaySoundOnDeath::C_PlaySoundOnDeath() : Component(false)
{
	int soundBufferId = SoundBufferManager::AddSoundBuffer("../resources/sounds/snd_enemy_dead.wav");
	sound.setBuffer(SoundBufferManager::GetSoundBuffer(soundBufferId));
	sound.setAttenuation(5.f);
	sound.setMinDistance(80.f);
}


C_PlaySoundOnDeath::~C_PlaySoundOnDeath()
{
	//TODO: go through every class and work out how to un-initialise! and if it is even necessary in most cases.
}

void C_PlaySoundOnDeath::LoadDependencies(Object* owner)
{
	//owner->GetComponent<C_Health>()->PerformActionOnDeath(OnDeath);
	m_transform = owner->m_transform;
}

void C_PlaySoundOnDeath::OnDeath()
{
	const sf::Vector2f& position = m_transform->GetPosition();

	// Generate and set a random pitch.
	float pitch = (std::rand() % 11 + 95) / 100.f;
	sound.setPitch(pitch);

	// Set the position of the sound.
	sound.setPosition(position.x, position.y, 0.f);

	// Play the sound.
	sound.play();
}
