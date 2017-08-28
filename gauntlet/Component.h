#pragma once


//TODO: Add requires component i.e. sprite component requires transform component.
//TODO: Add reset method to each component.
class Component
{
	friend class Object;
public:
	Component(bool requireUnique) : m_unique(requireUnique){}
	~Component() {}

	virtual void LoadDependencies(Object* owner){}

	virtual void Update(float deltaTime){}

	bool RequiresUnique()
	{
		return m_unique;
	}

protected:
	//Object* m_owner;
	bool m_unique;
};

