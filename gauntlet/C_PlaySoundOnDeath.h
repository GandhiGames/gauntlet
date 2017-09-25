#pragma once

#include "C_Transform.h"

class C_PlaySoundOnDeath : public Component
{
public:
	C_PlaySoundOnDeath(Object* owner);
	~C_PlaySoundOnDeath();

	void LoadDependencies(Object* owner) override;

private:
	void OnDeath();

private:
	sf::Sound sound;

	std::shared_ptr<C_Transform> m_transform;
};

