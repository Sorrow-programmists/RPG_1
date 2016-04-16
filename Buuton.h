#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>

using namespace sf;

class Buutons
{
private: int weight = 0;
private: int height = 0;
public: bool work = true;
private: Sprite sprite;
private: Texture texture;
private: Vector2f posf;
private: Vector2i posi;
private: IntRect Rect;
private: bool drawing = true;
public: bool ifBuutonCoordRegr(int x,int y)//паполи на кнопку или нет
{
	int X = x;
	int Y = y;
	bool returned = false;
	if (work)
	{
		posf = sprite.getPosition();
		if ((X >= posf.x) && (Y >= posf.y) && (X <= weight + posf.x) && (Y <= height + posf.y))
			returned = true;
	}
	return returned;
}
public: void setPosition(float X, float Y)
{
	sprite.setPosition(X, Y);
} 
public: Vector2f getPosition()
{
	return sprite.getPosition();
}
public: void show(RenderWindow &_window)
{
	if (drawing)
	_window.draw(sprite);
}
public: Buutons(char str[80], int X, int Y, int _weight, int _height, bool _work = true)
{
	texture.loadFromFile(str);
	work = _work;
	posi.x = X;
	posi.y = Y;
	weight = _weight;
	height = _height;
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, weight, height)); sprite.setPosition(X,Y);
}
public: void changeTexture(char str[80])
{
	texture.loadFromFile(str);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, weight, height)); 
}
public: void deleteB()
{
	drawing = false;
}
};