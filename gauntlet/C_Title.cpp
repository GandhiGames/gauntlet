#include "PCH.h"
#include "C_Title.h"
#include "Object.h"

C_Title::C_Title() : Component(true),
	m_name(""),
	m_textOffset({ 0.f, 0.f })
{
	// Load font.
	m_font.loadFromFile("../resources/fonts/ADDSBP__.TTF");
	m_text.setFont(m_font);

	// Setup the text.
	m_text.setCharacterSize(12);
}


C_Title::~C_Title()
{
}

void C_Title::LoadDependencies(Object* owner)
{
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
	// Store new name.
	m_name = name;

	// Set the item name.
	std::ostringstream ss;
	ss << m_name;
	std::string str(ss.str());
	m_text.setString(str);

	// Store the text offset needed when drawing.
	m_textOffset = sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
}

void C_Title::Draw(sf::RenderWindow& window, float timeDelta)
{
	const sf::Vector2f& pos = m_transform->GetPosition();
	m_text.setPosition(pos.x - m_textOffset.x, (pos.y - 30.f) - m_textOffset.y);
	window.draw(m_text);
}
