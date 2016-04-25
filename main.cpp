#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "iostream"
#include "level.h"
#include <algorithm>


int arg = 0;

using namespace sf;
Level lvl;
View view;
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

			}
	}

};
struct State
{
	int a = 0;
	
};
State s;
void game(RenderWindow &, View &);
void pause(RenderWindow &, View &);
void menu(RenderWindow &window,View &view)
{
	Texture texture;
	texture.loadFromFile("images/map.png");
	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(0, 0);
	while (window.isOpen()&&StateStack::isWorked(menu)){
		Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed)
				StateStack::popAll();
		if (Keyboard::isKeyPressed(Keyboard::Escape)){
			StateStack::popAll();
		}
		if (Keyboard::isKeyPressed(Keyboard::G)){
			StateStack::popAll();
			StateStack::push(game);
		}
		window.clear();
		window.draw(sprite);
		window.display();
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
			StateStack::popAll();
			StateStack::push(game);
		}
	}
}
void game(RenderWindow &window,View &view)
{
	lvl.LoadFromFile("map.tmx");
	Object player = lvl.GetObject("player");
	Player p("images/Map.png", player.rect.left, player.rect.top);
	while (window.isOpen() && StateStack::isWorked(game)){
		window.setView(view);
		window.clear(Color::Yellow);
		lvl.Draw(window);
		window.draw(p.sprite);
		window.display();
		Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed){
				StateStack::popAll();
			}
		if (Keyboard::isKeyPressed(Keyboard::Escape)){
			StateStack::popAll();
			StateStack::push(pause);
			StateStack::perform(window,view);
		}

	}
}
int main()
{
	RenderWindow window(VideoMode(640, 480), "F14");
	view.reset(FloatRect(0, 0, 640, 480));
	StateStack::push(menu);
	while (StateStack::isWorked(menu) || StateStack::isWorked(game))
	{
		StateStack::perform(window,view);
	}
	//switch (s.a)
	//{
	//case 1:menu(window, view);
	//case 2:game(window, view);
	//}
	//StateStack::perform(window, view);
	return 0;
}
