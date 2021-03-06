﻿#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "iostream"
#include "level.h"
#include <algorithm>


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
		sprite.setPosition(x, y);
	}

	void checkCollisionWithMap()
	{
		for (int i = 0; i<obj.size(); i++)
			if (FloatRect(x, y, 32, 32).intersects(obj[i].rect))
			{
				//ïðèãîäèòñÿ
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
	static auto current() -> decltype(_state.at(0))
	{
		return _state.at(_state.size() - 1);
	}
	static void popAll()
	{
		_state.clear();
	}
	static bool isWorked(void(*state)(RenderWindow&, View&))
	{
		return (find(_state.begin(), _state.end(), state) != _state.end());
	}
};
std::vector<void(*)(RenderWindow&, View&)> StateStack::_state;

void pause(RenderWindow&, View&);

void game(RenderWindow&, View&);

void menu(RenderWindow& window, View& view)
{
	view.setCenter(320,240);
	window.setView(view);
	while (window.isOpen() && StateStack::isWorked(menu))
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
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
			StateStack::popAll();
		}
		if (Keyboard::isKeyPressed(Keyboard::G))
		{
			StateStack::popAll();
			StateStack::push(game);
		}
		window.display();
	}
}
void game(RenderWindow& window, View& view)
{
	lvl.LoadFromFile("map.tmx");
	Object player = lvl.GetObject("player");
	Player p("images/Map.png", player.rect.left, player.rect.top);
	while (window.isOpen() && StateStack::isWorked(game))
	{

		view.setCenter(player.rect.left + 16, player.rect.top + 16);
		window.setView(view);
		window.clear();
		lvl.Draw(window);
		window.draw(p.sprite);
		window.display();
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
			StateStack::push(pause);
			StateStack::perform(window, view);
		}
	}
}
void pause(RenderWindow& window, View& view)
{
	while (window.isOpen() && StateStack::isWorked(pause))
	{
		window.clear(Color::Red);
		window.display();

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
			StateStack::push(menu);
		}
		if (Keyboard::isKeyPressed(Keyboard::G))
		{
			StateStack::pop();
		}
	}
}
int main()
{
	RenderWindow window(VideoMode(640, 480), "F14");
	view.reset(FloatRect(0, 0, 640, 480));
	StateStack::push(menu);
	while (window.isOpen())
		StateStack::perform(window, view);
	return 0;
}