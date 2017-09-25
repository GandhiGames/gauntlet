#pragma once

#include "C_Drawable.h"
#include "C_Updateable.h"
#include "C_Transform.h"
#include <assert.h>

class C_AnimatedSprite : public Component, public C_Drawable, public C_Updateable
{
	friend class Object;

public:
	C_AnimatedSprite(Object* owner);
	~C_AnimatedSprite();

	void LoadDependencies(Object* owner) override;

	void Update(float deltaTime, Object* owner) override;

	/**
	* Draws the object to the screen at its current position.
	* @param window The render window to draw the object to.
	* @param tileDelta The time, in MS, since the last draw call.
	*/
	virtual void Draw(sf::RenderWindow &window, float timeDelta) override;

	/**
	* Creates and sets the object sprite.
	* This function takes the location to a resource, and from that create a texture and sprite.
	* You can optionally specify animation properties. If set the frame dimensions will be calculated automatically.
	* If left blank, the whole resource will be used.
	* @param fileName The path to the resource that you wish to load, relative to the project.
	* @param frames The number of frames in the sprite. Defaults to 1.
	* @param frameSpeed The speed that the animation plays at. Defaults to 1.
	* @return true if the operation succeeded.
	*/
	bool SetSprite(sf::Texture& texture, bool isSmooth, int frames = 1, int frameSpeed = 0);

	/**
	* Returns a reference the object's sprite.
	* @return A reference to the object's sprite.
	*/
	sf::Sprite& GetSprite();

	void NextFrame();

	/**
	* Get the number of frames the object has.
	* @return The number of frames the object has.
	*/
	int GetFrameCount() const;

	void SetAnimated(bool animated);

	bool IsAnimated();

private:
	sf::Sprite m_sprite;

	std::shared_ptr<C_Transform> m_transform;

	bool m_animated;

	/**
	* The animation speed of the image if applicable.
	* Value is frames per second.
	*/
	int m_animationSpeed;

	/**
	* The total number of frames the sprite has.
	*/
	int m_frameCount;

	/**
	* The current frame of the sprite.
	*/
	int m_currentFrame;

	/**
	* The width of each frame of the animated sprite if applicable.
	*/
	int m_frameWidth;

	/**
	* The height of each frame of the animated sprite if applicable.
	*/
	int m_frameHeight;

	/**
	* An aggregate of the time passed between draw calls.
	*/
	float m_timeDelta;
};

