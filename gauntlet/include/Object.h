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
#include "C_StaticSprite.h"
#include "C_AnimatedSprite.h"
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
#include "C_AudioListener.h"
#include "C_ProjectileAttack.h"
#include "C_Tag.h"
#include "C_SpawnItemsOnDeath.h"
#include "C_PlaySoundOnDeath.h"
#include "C_InstanceID.h"
#include "C_Drawable.h"
#include "C_Updateable.h"
#include "C_ItemType.h"
#include "C_Projectile.h"
#include "C_Torch.h"
#include "C_PlayerTorch.h"
#include "C_Movement.h"
#include "C_KeyboardController.h"
#include "C_DirectionalAnimation.h"
#include "C_PlayerClass.h"
#include "C_Inventory.h"
#include "C_Collidable.h"
#include "C_Gold.h"
#include "C_DistanceBasedCollision.h"
#include "C_Gem.h"
#include "C_Key.h"
#include "C_Potion.h"
#include "C_Heart.h"
#include "C_Event.h"
#include "C_OnDeathListener.h"
#include "C_ClosestTorchSoundPosition.h"
#include "C_EndLevelTileCollision.h"
#include "C_CentreOnMousePosition.h"

//TODO: add fixed and late update
class Object
{
public:
	/**
	 * Default constructor.
	 */
	Object();

	/**
	 * Updates the game object. Called once per tick.
	 * @param timeDelta The time elapsed since the last tick in MS.
	 */
	virtual void Update(float timeDelta);

	void Draw(sf::RenderWindow &window, float timeDelta);

	void LateUpdate(float timeDelta);

	void OnCollisionEnter(Object* other);
	void OnCollisionExit(Object* other);

	//TODO: we don't want to have to remember to set context when creating new objects. Have this set somewhere else or through constructor.
	void SetContext(SharedContext* context);
	SharedContext* GetContext();

	void Destroy();

	bool IsQueuedForRemoval() const;

	/**
	* Attaches a component to the object.
	*/
	template <typename T> std::shared_ptr<T> AddComponent()
	{
		//static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
		
		std::shared_ptr<T> newComponent = std::make_shared<T>(this);

		if (newComponent->RequiresUnique())
		{
			// Check that we don't already have a component of this type.
			for (auto& exisitingComponent : m_components)
			{
				if (std::dynamic_pointer_cast<T>(exisitingComponent))
				{
					//TODO: create in-game debug/message log.
					std::cout << "Attempting to re-add component: " << newComponent << std::endl;
					return std::dynamic_pointer_cast<T>(exisitingComponent);
				}
			}
		}

		newComponent->LoadDependencies(this);
		m_components.push_back(newComponent);

		return newComponent;
	};

	/**
	* Gets a component from the object.
	*/
	template <typename T> std::shared_ptr<T> GetComponent()
	{
		//static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

		// Check that we don't already have a component of this type.
		for (auto& exisitingComponent : m_components)
		{
			if (std::dynamic_pointer_cast<T>(exisitingComponent))
			{
				return std::dynamic_pointer_cast<T>(exisitingComponent);
			}
		}

		return nullptr;
	};

	template <typename T> std::vector<std::shared_ptr<T>> GetComponents()
	{
		//static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

		std::vector<std::shared_ptr<T>> components;

		for (auto& exisitingComponent : m_components)
		{
			if (std::dynamic_pointer_cast<T>(exisitingComponent))
			{
				//TODO: change all to push_back?
				components.emplace_back(std::dynamic_pointer_cast<T>(exisitingComponent));
			}
		}

		return components;
	};

public:
	//TODO change to const getter method?
	std::shared_ptr<C_Transform> m_transform;
	std::shared_ptr<C_InstanceID> m_instanceID;
	std::shared_ptr<C_Tag> m_tag;
	
private:
	std::vector<std::shared_ptr<Component>> m_components;
	bool m_queuedForRemoval;
	SharedContext* m_context;
};
#endif