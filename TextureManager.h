#pragma once
#include <SFML\Graphics.hpp>    
#include <algorithm>

class TextureManager
{
public:
	static int loadImage(const std::string &filename)
	{
		sf::Image image;
		if (!image.loadFromFile(filename))
			return -1;
		_image.emplace_back(image);
		return _image.size() - 1;
	}

	static const sf::Texture * getTexture(int index)
	{
		return &_texture.at(index);
	}

	static const sf::Image * getImage(int index)
	{
		return &_image.at(index);
	}

	static int addImage(const sf::Image &image)
	{
		_image.emplace_back(image);
		return _image.size();
	}

	static int loadTextureFromImage(int index, sf::IntRect &area = sf::IntRect())
	{
		sf::Texture texture;
		texture.loadFromImage(_image.at(index), area);
		_texture.emplace_back(texture);
		return _texture.size() - 1;
	}

	static int makeSprite(const sf::Texture *texture = nullptr,sf::IntRect &area = sf::IntRect())
	{
		sf::Sprite sprite;
		if (texture != nullptr)
			sprite.setTexture(*texture);
		if (area != sf::IntRect())
			sprite.setTextureRect(area);
		_sprite.emplace_back(sprite);
		return _sprite.size() - 1;
	}

	static const sf::Sprite * getSprite(int index)
	{
		return &_sprite.at(index);
	}

	static int addTexture(const sf::Texture & texture)
	{
		_texture.emplace_back(texture);
		return _texture.size() - 1;
	}

	static int addSprite(const sf::Sprite &sprite)
	{
		_sprite.emplace_back(sprite);
		return _sprite.size() - 1;
	}

	static void drawSprite(sf::RenderWindow &window,int index)
	{
		window.draw(_sprite.at(index));
	}

private:
	static std::vector<sf::Texture> _texture;

	static std::vector<sf::Image> _image;

	static std::vector<sf::Sprite> _sprite;
};