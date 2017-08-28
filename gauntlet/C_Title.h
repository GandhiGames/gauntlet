#pragma once

#include "Component.h"

class C_Title : public Component
{
public:
	C_Title();
	~C_Title();

	std::string GetItemName() const;
	void Set(std::string name);

	void Draw(sf::RenderWindow& window, const sf::Vector2f& pos);

private:
	std::string m_name;
	sf::Text m_text;
	sf::Font m_font;
	sf::Vector2f m_textOffset;
};

