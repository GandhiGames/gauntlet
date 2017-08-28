#include "PCH.h"
#include "C_Sprite.h"
#include "Object.h"

C_Sprite::C_Sprite() : Component(true),
	m_animationSpeed(0),
	m_isAnimated(false),
	m_frameCount(0),
	m_currentFrame(0),
	m_frameWidth(0),
	m_frameHeight(0),
	m_timeDelta(0)
{
	
}

C_Sprite::~C_Sprite()
{
}

void C_Sprite::LoadDependencies(Object* owner) 
{
	m_transform = owner->m_transform;
}

void C_Sprite::Update(float deltaTime)
{
	m_sprite.setPosition(m_transform->GetPosition());
}

// Gives the object the given sprite.
bool C_Sprite::SetSprite(sf::Texture& texture, bool isSmooth, int frames, int frameSpeed)
{
	// Create a sprite from the loaded texture.
	m_sprite.setTexture(texture);

	// Set animation speed.
	m_animationSpeed = frameSpeed;

	// Store the number of frames.
	m_frameCount = frames;

	// Calculate frame dimensions.
	sf::Vector2u texSize = m_sprite.getTexture()->getSize();
	m_frameWidth = texSize.x / m_frameCount;
	m_frameHeight = texSize.y;

	// Check if animated or static.
	if (frames > 1)
	{
		// Set sprite as animated.
		m_isAnimated = true;

		// Set the texture rect of the first frame.
		m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
	}
	else
	{
		// Set sprite as non animated.
		m_isAnimated = false;
	}

	// Set the origin of the sprite.
	m_sprite.setOrigin(m_frameWidth / 2.f, m_frameHeight / 2.f);

	return true;
}

//TODO: remove this function and provide functionality through different methods.
sf::Sprite& C_Sprite::GetSprite()
{
	return m_sprite;
}

// Gets the current animation state of the object.
bool C_Sprite::IsAnimated()
{
	return m_isAnimated;
}

// Sets the animation state of the object.
void C_Sprite::SetAnimated(bool isAnimated)
{
	m_isAnimated = isAnimated;

	if (isAnimated)
	{
		m_currentFrame = 0;
	}
	else
	{
		// set the texture rect of the first frame
		m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
	}
}

// Draws the object to the given render window.
void C_Sprite::Draw(sf::RenderWindow &window, float timeDelta)
{
	// check if the sprite is animated
	if (m_isAnimated)
	{
		// add the elapsed time since the last draw call to the aggregate
		m_timeDelta += timeDelta;

		// check if the frame should be updated
		if (m_timeDelta >= (1.f / m_animationSpeed))
		{
			NextFrame();
			m_timeDelta = 0;
		}
	}

	window.draw(m_sprite);
}

// Advances the sprite forward a frame.
void C_Sprite::NextFrame()
{
	// check if we reached the last frame
	if (m_currentFrame == (m_frameCount - 1))
		m_currentFrame = 0;
	else
		m_currentFrame++;

	// update the texture rect
	m_sprite.setTextureRect(sf::IntRect(m_frameWidth * m_currentFrame, 0, m_frameWidth, m_frameHeight));
}

// Gets the frame count of the object.
int C_Sprite::GetFrameCount() const
{
	return m_frameCount;
}


