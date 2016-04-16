#pragma once
#include <SFML\Graphics.hpp>

class Object
{
protected:
	float X;
	float Y;

public:
	sf::Texture texture;
	sf::Sprite sprite;

	void draw(sf::RenderWindow &window)
	{
		sprite.setPosition(X, Y);
		window.draw(sprite);
	}
};