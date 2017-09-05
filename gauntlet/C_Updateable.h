#pragma once

//TODO: rename - remove C_
class C_Updateable 
{
	friend class Object;
public:
	C_Updateable();
	~C_Updateable();

	virtual void Update(float deltaTime, Object* owner) = 0;
};

