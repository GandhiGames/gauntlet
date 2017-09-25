#pragma once

//TODO: rename - remove C_
class C_Drawable 
{
public:
	C_Drawable();
	virtual ~C_Drawable();

	virtual void Draw(sf::RenderWindow &window, float timeDelta) = 0;

	void SetSortOrder(const int& order);
	const int& GetSortOrder();

private:
	int m_sortOrder;
};

