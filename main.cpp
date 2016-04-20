#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "iostream"
#include "level.h"
#include <vector>
#include <list>


int arg = 0;

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
		sprite.setPosition(x, y);
	}

	void checkCollisionWithMap()
	{
		for (int i = 0; i<obj.size(); i++)
			if (FloatRect(x, y, 32, 32).intersects(obj[i].rect))
			{
				//пригодится
			}
	}

};
class StateStack
{
private:
	static std::vector<void(*)(RenderWindow&, View&)> _state;
public:
	static void push(void(*state)(RenderWindow&, View&))
	{
		_state.push_back(state);
	}
	static void pop()
	{
		if (_state.size() == 1) popAll();
		else _state.pop_back();
	}
	static void perform(RenderWindow& window, View& view)
	{

		if (_state.empty()) return;
		_state.at(_state.size() - 1)(window, view);
	}
	static void popAll()
	{

		_state.clear();
	}
};
std::vector<void(*)(RenderWindow&, View&)> StateStack::_state;

void pause(RenderWindow&, View&);

void game(RenderWindow&, View&);

void menu(RenderWindow& window, View& view)
{
	bool MenuIsWorked = true;
	while (window.isOpen() && MenuIsWorked)
	{
		Event event;
		window.clear(Color::Blue);
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				StateStack::popAll();
			}
		}
		//
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
			StateStack::popAll();
		}
		//
		if (Keyboard::isKeyPressed(Keyboard::G))
		{
			MenuIsWorked = false;
			StateStack::popAll();
			StateStack::push(game);
		}
		//
		window.display();
	}
	StateStack::perform(window, view);
}
void game(RenderWindow& window, View& view)
{

	lvl.LoadFromFile("map.tmx");
	Object player = lvl.GetObject("player");
	Player p("images/Map.png", player.rect.left, player.rect.top);
	bool GameIsWorked = true;
	while (window.isOpen() && GameIsWorked)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				StateStack::popAll();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::P))
		{
			StateStack::popAll();
			StateStack::push(pause);
			StateStack::perform(window, view);
		}
		view.setCenter(player.rect.left, player.rect.top);
		window.setView(view);
		window.clear();
		lvl.Draw(window);
		window.draw(p.sprite);
		window.display();

	}
	StateStack::perform(window, view);
}
void pause(RenderWindow& window, View& view)
{

	bool PauseIsWorked = true;
	while (window.isOpen() && PauseIsWorked)
	{
		window.clear(Color::Red);
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				StateStack::popAll();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::M))
		{
			StateStack::popAll();
			PauseIsWorked = false;
			StateStack::push(menu);
		}
		if (Keyboard::isKeyPressed(Keyboard::G))
		{
			PauseIsWorked = false;
			StateStack::popAll();
			return;
		}
		window.display();
	}
	StateStack::perform(window, view);
}
int main()
{
	RenderWindow window(VideoMode(640, 480), "F14");
	view.reset(FloatRect(0, 0, 640, 480));
	StateStack::push(menu);
	StateStack::perform(window, view);
	return 0;
}
