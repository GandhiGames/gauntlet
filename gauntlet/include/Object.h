//-------------------------------------------------------------------------------------
// Object.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef OBJECT_H
#define OBJECT_H

#include<iostream>
#include "C_Sprite.h"
#include "C_Transform.h"
#include "C_Title.h"
#include "C_PointsOnPickup.h"
#include "C_Health.h"
#include "C_PotionType.h"
#include "C_Attack.h"
#include "C_Defense.h"
#include "C_Strength.h"
#include "C_Dexterity.h"
#include "C_Stamina.h"
#include "C_Mana.h"
#include "C_Pathfinding.h"

//TODO cache c_transform so all objects have access rather than needing to call getcomponent.
class Object
{
public:
	/**
	 * Default constructor.
	 */
	Object();

	/**
	 * Updates the game object. Called once per tick.
	 * This is a pure virtual function, and must be implemented by extending classes.
	 * @param timeDelta The time elapsed since the last tick in MS.
	 */
	virtual void Update(float timeDelta);

	/**
	* Attaches a component to the object.
	*/
	template <typename T> std::shared_ptr<T> AddComponent()
	{
		// First we'll create the component.
		std::shared_ptr<T> newComponent = std::make_shared<T>();
		newComponent->LoadDependencies(this);

		if (newComponent->RequiresUnique())
		{
			// Check that we don't already have a component of this type.
			for (std::shared_ptr<Component>& exisitingComponent : m_components)
			{
				if (std::dynamic_pointer_cast<T>(exisitingComponent))
				{
					//TODO: create in-game debug/message log.
					std::cout << "Overwritting component: " << newComponent << std::endl;
					exisitingComponent = newComponent;
					return newComponent;
				}
			}
		}

		// The component is the first of its type so add it.
		m_components.push_back(newComponent);

		// Return the new component.
		return newComponent;
	};

	/**
	* Gets a component from the object.
	*/
	template <typename T> std::shared_ptr<T> GetComponent()
	{
		// Check that we don't already have a component of this type.
		for (std::shared_ptr<Component> exisitingComponent : m_components)
		{
			if (std::dynamic_pointer_cast<T>(exisitingComponent))
			{
				return std::dynamic_pointer_cast<T>(exisitingComponent);
			}
		}

		return nullptr;
	};

public:
	//TODO change to const getter method.
	std::shared_ptr<C_Transform> m_transform;
	
private:
	std::vector<std::shared_ptr<Component>> m_components;
};
#endif