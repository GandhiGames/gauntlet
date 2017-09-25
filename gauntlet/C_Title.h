#pragma once

#include "C_Drawable.h"
#include "C_Transform.h"

//TODO: rename to text.
class C_Title : public Component, public C_Drawable
{
public:
	C_Title(Object* owner);
	~C_Title();

	void LoadDependencies(Object* owner) override;

	//TODO: rename 'Get'
	std::string GetItemName() const;
	void Set(std::string name);

	void Draw(sf::RenderWindow& window, float deltaTime) override;

private:
	std::string m_name;
	sf::Text m_text;
	sf::Font m_font;
	sf::Vector2f m_textOffset;

	std::shared_ptr<C_Transform> m_transform;
};

