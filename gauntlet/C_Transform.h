#pragma once

#include "Component.h"

//TODO: tidy up bracket convention (below or besides!) { vs
//{
// find setting in vs to do it for me.

//TODO: have method of marking transform static so that sprite (and any other components that rely on it) do
// not keep polling getposition.

// Automatically added to all new objects.
class C_Transform : public Component
{
public:
	C_Transform(Object* owner);
	~C_Transform();

	/**
	* Sets the position of the object on screen. This is relative to the top-left of the game window.
	* @param position The new position of the player.
	*/
	void SetPosition(sf::Vector2f position);

	void SetPosition(float x, float y);

	void SetX(float x);

	void SetY(float y);

	/**
	* Returns the position of the object. This is relative to the top-left of the game window.
	* @return The position of the object
	*/
	const sf::Vector2f& GetPosition() const;

	void SetParent(std::shared_ptr<C_Transform> parent);
	const std::shared_ptr<C_Transform> GetParent() const;

	void AddChild(C_Transform* child);
	const std::vector<C_Transform*>& GetChildren() const;


private:
	/**
	* The position of the object in the game window.
	*/
	sf::Vector2f m_position;
	std::shared_ptr<C_Transform> m_parent;
	std::vector<C_Transform*> m_children;
};