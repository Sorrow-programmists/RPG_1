#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>

using namespace sf;

class Buttons
{
private: int weight = 0;
private: int height = 0;
public: bool work = true;
private: Sprite sprite;
private: Image image1;
private: Image image2;
private: int Nimg = 0;
private: Texture texture;
private: Vector2f posf;
private: Vector2i posi;
private: IntRect Rect;
private: bool drawing = true;
public: bool isBuutonCoord(int x,int y)
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
public: void show(RenderWindow &window)
{
	if (drawing)
	window.draw(sprite);
}
public: Buttons(Image img1,Image img2, int X, int Y, int _weight = 128, int _height = 64, bool _work = true)
{
	image1 = img1;
	image2 = img2;
	texture.loadFromImage(image1);
	work = _work;
	posi.x = X;
	posi.y = Y;
	weight = _weight;
	height = _height;
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, weight, height)); sprite.setPosition(X,Y);
}
public: void changeTexture(Image img)
{
	if (Nimg) {
		texture.loadFromFile(image1); 
		Nimg = 0;
	}else 
	{
		Nimg = 1;
		texture.loadFromFile(image2); 
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, weight, height)); 
}
public: void Drawable()
{
	drawing = !drawing;
}
};
