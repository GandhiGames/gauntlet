#pragma once


//TODO: Add requires component i.e. sprite component requires transform component.
//TODO: Add reset method to each component (used by object pool when created).
class Component
{
	friend class Object;
public:
	Component(Object* owner, bool requireUnique) : m_unique(requireUnique), m_owner(owner)
	{
	}
	
	~Component() {}

	virtual void LoadDependencies(Object* owner){}

	bool RequiresUnique()
	{
		return m_unique;
	}

public:
	//TODO: getters/setters
	Object* m_owner;

protected:
	bool m_unique;

	
};

