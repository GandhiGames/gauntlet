#pragma once


//TODO: Add requires component i.e. sprite component requires transform component.
//TODO: Add reset method to each component (used by object pool when created).
class Component
{
	friend class Object;
public:
	Component(bool requireUnique) : m_unique(requireUnique){}
	
	~Component() {}

	virtual void LoadDependencies(Object* owner){}

	bool RequiresUnique()
	{
		return m_unique;
	}

protected:
	bool m_unique;
};

