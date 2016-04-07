#include <SFML\Graphics.hpp>
#include <cstdint>
#include <algorithm>
#include <map>
#include "TextureManager.h"

class Map {
public:

	Map(int width,int height) : _width(width), _height(height)
	{
		_map = new uint8_t*[width];
		for (int i(0); i < width; i++)
			_map[i] = new uint8_t[height];
	}

	char getMapCode(int X,int Y)
	{
		return _map[X][Y];
	}

	void setMapCode(int X, int Y, uint8_t code)
	{
		_map[X][Y] = code;
	}

	void setMapkDefault()
	{
		for (int g(0); g < _height; g++)
			for (int i(0); i < _width; i++)
				_map[i][g] = (rand()%3);
		
	}

	void setTexture(sf::Image * image)
	{
		_image = TextureManager::addImage(*image);
	}

	void loadTextureFromImage(const sf::IntRect &size)
	{
		_fullTexture = TextureManager::loadTextureFromImage(*_image);
		for (int i(0); i < _image->getSize().x; i += size.width)
		{
			for (int j(0); j < _image->getSize().y; j += size.height)
			{
				sf::Sprite sprite;
				sprite.setTexture(*_fullTexture);
				sprite.setTextureRect(sf::IntRect(size.left + i, size.top + j, size.width, size.height));
				TextureManager::makeSprite();
				_texture.insert(std::pair<int,sf::Sprite*>(_texture.size() + 1, &sprite));
			}
		}
	}

	void drawMap(sf::RenderWindow &window, const sf::IntRect &area)
	{
		if (!_texture.empty())
		{
			
			for (int i(area.left); i < (area.left + area.width) / _texture.at(0)->getLocalBounds().width; i++)
				for (int j(area.top); j < (area.top + area.height) / _texture.at(0)->getLocalBounds().height; j++)
				{
					window.draw(*_texture.at(_map[i][j]));
				}
			return;
		}
	}

	~Map()
	{
		for (int i(0); i < _width; i++)
			delete[] _map[i];
		delete[] _map;
	}

private:
	int _width, _height;

	uint8_t **_map;

	std::map<int, sf::Sprite*> _texture;

	sf::Image *_image;

	sf::Texture *_fullTexture;
};