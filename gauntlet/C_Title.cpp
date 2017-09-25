#include "PCH.h"
#include "C_Title.h"
#include "Object.h"

C_Title::C_Title(Object* owner) : Component(owner, true),
	m_name(""),
	m_textOffset({ 0.f, 0.f })
{
	
}


C_Title::~C_Title()
{
}

void C_Title::LoadDependencies(Object* owner)
{
	assert(owner->GetComponents<C_Drawable>().size() == 0);

	m_transform = owner->m_transform;
}

// Gets the name of the item.
std::string C_Title::GetItemName() const
{
	return m_name;
}

// Sets the item name.
void C_Title::Set(std::string name)
{
	//TODO: this was moved from the constructor as copy constructor for text does not copy font! 
	// write copy operator
	if (m_text.getFont() == nullptr)
	{
		// Load font.
		m_font.loadFromFile("../resources/fonts/ADDSBP__.TTF");
		m_text.setFont(m_font);

		// Setup the text.
		m_text.setCharacterSize(12);
	}

	// Store new name.
	m_name = name;

	// Set the item name.
	//std::ostringstream ss;
	//ss << m_name;
	//std::string str(ss.str());
	m_text.setString(m_name);

	// Store the text offset needed when drawing.
	m_textOffset = sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
}

void C_Title::Draw(sf::RenderWindow& window, float timeDelta)
{
	const sf::Vector2f& pos = m_transform->GetPosition();
	m_text.setPosition(pos.x - m_textOffset.x, (pos.y - 30.f) - m_textOffset.y);
	window.draw(m_text);
}
