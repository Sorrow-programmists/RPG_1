#pragma once
#include <SFML\Graphics.hpp>    
#include <algorithm>

class TextureManager
{
public:
	static sf::Image * loadImage(const std::string &filename)
	{
		sf::Image image;
		if (!image.loadFromFile(filename))
			return nullptr;
		_image.emplace_back(image);
		return &_image.at(_image.size() - 1);
	}

	static sf::Image * addImage(const sf::Image &image)
	{
		_image.emplace_back(image);
		return &_image.at(_image.size() - 1);
	}

	static sf::Texture * loadTextureFromImage(sf::Image &image, sf::IntRect &area = sf::IntRect())
	{
		sf::Texture texture;
		texture.loadFromImage(image, area);
		_texture.emplace_back(texture);
		return &_texture.at(_texture.size() - 1);
	}

	static sf::Sprite * makeSprite(const sf::Texture *texture = nullptr, sf::IntRect &area = sf::IntRect(),
		sf::Vector2f position = sf::Vector2f(0, 0), float rotation = 0,
		sf::Color color = sf::Color(255, 255, 255, 255), sf::Vector2f scale = sf::Vector2f(0, 0))
	{
		sf::Sprite sprite;
		if (texture != nullptr)
			sprite.setTexture(*texture);
		if (area != sf::IntRect())
			sprite.setTextureRect(area);

		sprite.setRotation(rotation);
		sprite.setPosition(position);
		sprite.setScale(scale);
		sprite.setColor(color);

		_sprite.emplace_back(sprite);
		return &_sprite.at(_sprite.size() - 1);
	}

	static sf::Texture * addTexture(const sf::Texture & texture)
	{
		_texture.emplace_back(texture);
		return &_texture.at(_texture.size() - 1);
	}

	static sf::Sprite * addSprite(const sf::Sprite &sprite)
	{
		_sprite.emplace_back(sprite);
		return &_sprite.at(_sprite.size() - 1);
	}

	static void draw(sf::RenderWindow &window, const sf::Drawable &drawable)
	{
		window.draw(drawable);
	}

	static void quickDraw(sf::RenderWindow &window, const std::string &filename, sf::IntRect &area = sf::IntRect(),
		sf::Vector2f position = sf::Vector2f(0, 0), float rotation = 0,
		sf::Color color = sf::Color(255, 255, 255, 255), sf::Vector2f scale = sf::Vector2f(0, 0))
	{
		sf::Texture texture;
		texture.loadFromFile(filename);
		void * ind = addTexture(texture);
		ind = makeSprite((sf::Texture*)ind, area, position, rotation, color, scale);
		draw(window, *(sf::Sprite*)ind);
	}

private:
	static std::vector<sf::Texture> _texture;

	static std::vector<sf::Image> _image;

	static std::vector<sf::Sprite> _sprite;
};