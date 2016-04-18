#pragma once
#include <SFML\Graphics.hpp>

class Object
{
protected:
	sf::Sprite sprite;
public:
	const sf::Sprite &getSprite() const
	{
		return sprite;
	}
};