#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "iostream"
#include "level.h"
#include <vector>
#include <list>


using namespace sf;
Level lvl;
View view;
class Player {
public:
	std::vector<Object> obj;
	float x, y;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(char *chr, float X, float Y){
		image.loadFromFile(chr);
		    obj = lvl.GetAllObjects();
			x = X;
			y = Y;
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(0, 0, 32, 32));
			sprite.setPosition(x,y);
	   }
	
	   void checkCollisionWithMap()
	   {
		   for (int i = 0; i<obj.size(); i++)
		   if (FloatRect(x,y,32,32).intersects(obj[i].rect))
		   {
			  //пригодится
		   }
	   }
	
};




int main()
{
	RenderWindow window(VideoMode(640, 480), "F14");
	view.reset(FloatRect(0, 0, 640, 480));

	lvl.LoadFromFile("map.tmx");
	Object player=lvl.GetObject("player");
	Player p("images/Map.png", player.rect.left, player.rect.top);

	while (window.isOpen())
	{

		
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();	
		}		
		view.setCenter(p.x,p.y);
		window.setView(view);
		window.clear();
		lvl.Draw(window);

		window.draw(p.sprite);
		window.display();
	}
	return 0;
}
