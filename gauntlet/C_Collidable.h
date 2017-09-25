#pragma once

//TODO: rename - remove C_
class C_Collidable
{
	friend class Object;

public:
	C_Collidable();
	virtual ~C_Collidable() = 0;

	virtual void OnCollisionEnter(Object* owner, Object* other) {};
	virtual void OnCollisionExit(Object* owner, Object* other) {};
}; 

