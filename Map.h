#include <SFML\Graphics.hpp>
#include <cstdint>
#include <algorithm>
#include <map>
#include "TextureManager.h"
#include "Object.h"
#include <iostream>

class Map {
public:

	Map(int widthOfMap,int heightOfMap, int widthOfSprite, int heightOfSprite) 
		: _width(widthOfMap), _height(heightOfMap), _widthS(widthOfSprite), _heightS(heightOfSprite)
	{
		_map = new uint8_t*[_width];
		for (int i(0); i < _width; i++)
			_map[i] = new uint8_t[_height];
	}

	const char &getMapCode(int X,int Y) const
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
	void setObject(const Object &obj, const unsigned int &index)
	{
		_obj.insert(std::pair<int,Object>(index, obj));
	}
	const std::map<int, Object> &getStlMap() const
	{
		return _obj;
	}

	const Object &getObject(const unsigned int &index) const
	{
		return _obj.at(index);
	}
	/*
	void setTexture(const sf::Image & image)
	{
		_image = image;
	}
	void loadSpriteFromImage(const sf::IntRect &size)
	{
		_fullTexture.loadFromImage(_image);
		for (int i(0); i < _image.getSize().x; i += size.width)
		{
			for (int j(0); j < _image.getSize().y; j += size.height)
			{
				sf::Sprite sprite;
				sprite.setTexture(_fullTexture);
				sprite.setTextureRect(sf::IntRect(size.left + i, size.top + j, size.width, size.height));
				_sprite.emplace_back(sprite);
			}
		}
	}*/
	std::vector<int> getMapIndexList()
	{
		std::vector<int> v;
		for (int i(0); i < _width; i++)
			for (int j(0); j < _height; j++)
			{
				auto f = std::find(v.begin(),v.end(),_map[i][j]);
				if (f != v.end())
				{
					v.push_back(_map[i][j]);
				}
			}
		std::sort(v.begin(), v.end());
		return v;
	}
	void setSpriteSize(int width, int height)
	{
		_width = width;
		_height = height;
	}
	void drawMap(sf::RenderWindow &window, const sf::IntRect &area)
	{
		if (!_obj.empty())
		{
			
			for (int i(area.left); i < (area.left + area.width); i+= _widthS)
				for (int j(area.top); j < (area.top + area.height); j+= _heightS)
				{
					sf::Sprite sprite(_obj.at(_map[i][j]).getSprite());
					sprite.setTextureRect(sf::IntRect(i, j, _widthS, _heightS));
					window.draw(sprite);
				}
			return;
		}
	}
	const sf::Vector2u &getSize() const
	{
		return sf::Vector2u(_width, _height);
	}
	const sf::Vector2u &getSpriteSize() const
	{
		return sf::Vector2u(_widthS, _heightS);
	}

	~Map()
	{
		for (int i(0); i < _width; i++)
			delete[] _map[i];
		delete[] _map;
	}
	

	Map &operator=(const Map &right)
	{
		return Map(right);
	}

	Map(const Map &right)
	{
		_height = right.getSize().y;
		_width = right.getSize().x;

		_widthS = right.getSpriteSize().x;
		_heightS = right.getSpriteSize().y;


		_map = new uint8_t*[_width];
		for (int i(0); i < _width; i++)
			_map[i] = new uint8_t[_height];

		for (int i(0); i < _width; i++)
			for (int j(0); j < _height; j++)
				_map[i][j] = right.getMapCode(i, j);
		_obj = right.getStlMap();
	}
	
private:
	int _widthS, _heightS;

	uint8_t **_map;

	std::map<int,Object> _obj;

	int _width, _height;
	/*
	sf::Image _image;

	sf::Texture _fullTexture;
	
	
	template<class _lnlt,class Ty>
	_lnlt _findSorted(_lnlt begin, _lnlt end, Ty && val)
	{
		if begin
		_lnlt t = (begin + end) / 2;
		
	}*/
};



