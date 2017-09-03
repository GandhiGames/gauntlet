#pragma once

#include "Component.h"
#include "C_Transform.h"

class C_AudioListener : public Component
{
public:
	C_AudioListener();
	~C_AudioListener();

	void LoadDependencies(Object* owner) override;

	void Update(float deltaTime) override;

private:
	std::shared_ptr<C_Transform> m_transform;
};

