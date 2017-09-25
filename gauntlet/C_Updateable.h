#pragma once

//TODO: rename - remove C_
class C_Updateable 
{
	friend class Object;
public:
	C_Updateable();
	virtual ~C_Updateable() = 0;

	virtual void Update(float deltaTime, Object* owner) {}

	virtual void LateUpdate(float deltaTime, Object* owner) {}
};

